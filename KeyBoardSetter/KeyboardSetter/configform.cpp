#include "configform.h"
#include "configsaver.h"
#include "customkeyboard.h"
#include "ui_configform.h"
#include "uipainter.h"
#include "userconfig.h"
#include <QDebug>
#include <QLabel>
#include <qjsonobject.h>
#include <qpushbutton.h>

void initUI(QWidget* qw);

QVector<QPushButton *> *vkey_list;
CustomKeyboard *my_ckb;
HIDCodeTable table;
int row = 2;
int col = 5;

//current pressed key
QVector<int> cur_key_sp;
QVector<int> cur_key_normal;
int cur_mouse =0;
int cur_media =0;
int cur_delay =0;

//current select keyboard
int cur_keyboard_no = 0;//-1 repersent none
int cur_edit_key_no = -1;


ConfigForm::ConfigForm(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::ConfigForm)
{
    ui->setupUi(this);
    if(translator == NULL){
        translator = new QTranslator();
    }

    //load from config
    ConfigSaver cs;
    QString filename =  QCoreApplication::applicationDirPath() + "//usercondif.ini";
    QJsonObject *jsonobj = new QJsonObject();
    if(!cs.readConfig(filename,jsonobj))
        qDebug() << "Can not read userconfig.ini";
    UserConfig *uc = UserConfig::fromJson(*jsonobj);
    if(uc->getLanguage()=="english"){
        changeLanguage("en");
    }else{
        changeLanguage("cn");
    }
    initUI(this);
    //CONNECT FUNCTIONS
    for(int i = 1;i<vkey_list->size()+1;i++){
        connect(vkey_list->data()[i-1],&QPushButton::clicked,this,[=]{
            softKeyPressed(i);
        });
    }
    for(int i =0;i<row*col;i++){
        for(int j =0;j<my_ckb->getKeynum();j++){
            connect(my_ckb->getButtonByID(j),&QPushButton::clicked,this,[=]{
                setKey(j);
            });
        }
    }

}
//soft key press function
void ConfigForm::softKeyPressed(int i){
    ui->btn_setadd->show();
    if(table.isSPkey(i)){
        //clear single key except normal key
        cur_media = 0;
        cur_mouse = 0;
        //special key pressed
        if(cur_key_sp.indexOf(i)>=0){
            //the key is pressed
            cur_key_sp.remove(cur_key_sp.indexOf(i));
            keyboard_list_g[i-1]->setStyleSheet("");
        }
        else{
            //key is not pressed
            cur_key_sp.append(i);
            //set keys color
            keyboard_list_g[i-1]->setStyleSheet("background-color: rgb(255, 100, 100);");
        }
    }
    else if(table.isMouseKey(i)){
        //clear other single key
        cur_media = 0;
        //clear noraml
        if(cur_key_normal.size()>0){
            cur_key_normal[0]=0;
            cur_key_sp.clear();
        }
        if(cur_mouse==i)
            cur_mouse = 0;
        else{
            cur_mouse = i;
            addKeyValue();
        }
    }
    else if(table.isMediaKey(i)){
        //clear other single key
       cur_mouse = 0;
       if(cur_key_normal.size()>0){
           cur_key_normal[0]=0;
           cur_key_sp.clear();
       }
       if(cur_media==i)
           cur_media = 0;
       else{
           cur_media = i;
           addKeyValue();
       }
    }
    else
    {
        //clear other single key
        cur_media = 0;
        cur_mouse = 0;
        //normal key pressed
        if(cur_key_normal.indexOf(i)>=0)
            cur_key_normal.clear();
        else{
            cur_key_normal.clear();
            cur_key_normal.append(i);
            addKeyValue();
        }
    }
    updateUI();
}


ConfigForm::~ConfigForm()
{
    delete ui;
}



void ConfigForm::changeLanguage(QString language){
    QString flag = "english";
    if(language=="cn"){
        QString path = QCoreApplication::applicationDirPath() + "//trans_zh_CN.qm";
        translator->load(path);
        if(qApp->installTranslator(translator)){
            qDebug() << "Using chinese as UI language.";
            flag = "chinese";
        }
        else{
            qDebug() << "Can not load UI language:cn";
        }
    }else if(language=="en"){
        QString path = QCoreApplication::applicationDirPath() + "//trans_en_US.qm";
        bool is_load = translator->load(path);
        if(qApp->installTranslator(translator) && is_load){
            qDebug() << "Using english as UI language.";
            flag = "english";
        }
        else{
            qDebug() << "Can not load UI language:en";
        }
    }

    //save user language information to file
    UserConfig *userconfig = new UserConfig(flag);
    ConfigSaver cs;
    QString filename =  QCoreApplication::applicationDirPath() + "//usercondif.ini";
    if(!cs.saveConfig(filename,userconfig->toJsonObj()))
        qDebug()  << cs.getLastError();
    delete userconfig;
}

void initUI(QWidget* qw){
    UIPainter *painter = new UIPainter(qw,qw);
    painter->drawCKB(450-(int)(painter->getCKBWigth(col)/2),painter->getUI_part_margin(),col,row);

    painter->drawOutputPort(painter->getUI_part_margin(),painter->getCKBHeight(row)+50);

    painter->drawSwitch(painter->getUI_part_margin(),painter->getCKBHeight(row)+painter->getPortHeight()+55);

    painter->drawVKBfull(painter->getUI_part_margin(),painter->getCKBHeight(row)+painter->getPortHeight()+80);

    //test show_only_mouse
    //painter->hideVKB();
    painter->drawVMouse(painter->getUI_part_margin(),painter->getCKBHeight(row)+painter->getPortHeight()+80);
    painter->hideVMouse();
    painter->drawADVpanel(painter->getUI_part_margin(),painter->getCKBHeight(row)+painter->getPortHeight()+80);
    painter->hideAdvPanel();

    QVector<QPushButton*> *temp = painter->getSW_list();

    qw->connect(temp->data()[0],&QPushButton::clicked,qw,[=]{
        painter->switchVinput(painter->VKEYBOARD);
    });
    qw->connect(temp->data()[1],&QPushButton::clicked,qw,[=]{
        painter->switchVinput(painter->VMOUSE);
    });
    qw->connect(temp->data()[2],&QPushButton::clicked,qw,[=]{
        painter->switchVinput(painter->VADVANCE);
    });
    painter->triggerSwitch(0);

    qw->setFixedSize(1000,painter->getFullWindowHeight(row));
    //button init
    vkey_list = painter->getVkey_list();
    QVector<QPushButton *> *ckbkey_list = painter->getCKBkey_list();
    my_ckb = new CustomKeyboard("Test",10,0x2019,0x5131,ckbkey_list);

    //version justify
    int fwversion = 0;
    fwversion = my_ckb->getVersion();
    if(fwversion == 0){
        qDebug() << "device firmware is old,reset limits.";
        my_ckb->setMacroConfig(40,4,10,10);
    }
    else if(fwversion == 1){
        qDebug()<<"device firmware is new";
    }else{
        qDebug()<<"device not found.";
    }


}

