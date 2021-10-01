#include "configform.h"
#include "configsaver.h"
#include "customkeyboard.h"
#include "ui_configform.h"
#include "uipainter.h"
#include "userconfig.h"
#include <QDebug>
#include <QLabel>
#include <qjsonobject.h>
#include <qmessagebox.h>
#include <qpushbutton.h>

void initUI(QWidget* qw);
void updateUI();

QVector<QPushButton *> *vkey_list;
CustomKeyboard *my_ckb;
HIDCodeTable table;
UIPainter *painter;
int row = 2;
int col = 5;

//current pressed key
QVector<int> cur_key_sp;
QVector<int> cur_key_normal;
int cur_mouse =0;
int cur_media =0;
int cur_delay =0;

//current select keyboard
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
                cur_edit_key_no = j;
            });
        }
    }

}
//soft key press function
void ConfigForm::softKeyPressed(int i){
    painter->getBtn_addkey()->show();
    if(table.isSPkey(i)){
        //clear single key except normal key
        cur_media = 0;
        cur_mouse = 0;
        //special key pressed
        if(cur_key_sp.indexOf(i)>=0){
            //the key is pressed
            cur_key_sp.remove(cur_key_sp.indexOf(i));
            //keyboard_list_g[i-1]->setStyleSheet("");
            painter->setVkeyUntriggered(i-1);
        }
        else{
            //key is not pressed
            cur_key_sp.append(i);
            //set keys color
            //keyboard_list_g[i-1]->setStyleSheet("background-color: rgb(255, 100, 100);");
            painter->setVkeyTriggered(i-1);
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
void ConfigForm::showWarningDialog(QString title,QString content){
    QMessageBox msg_info(this);
    msg_info.setWindowTitle(title);
    msg_info.setText(content);
    msg_info.setIcon(QMessageBox::Critical);
    msg_info.setStandardButtons(QMessageBox::Ok);
    msg_info.exec();
}
bool ConfigForm::addKeyValue()
{
    //set append key value
    QVector<KeyValue*> temp_list = my_ckb->getCustomKeyByID(cur_edit_key_no)->getKeyValueList();
    int temp_normal = 0;
    if(cur_key_normal.size() > 0)
        temp_normal = cur_key_normal[0];
    KeyValue *temp_kv = table.convertVector2KeyValue(temp_normal,cur_mouse,cur_media,cur_key_sp);
    temp_kv->setDelay(cur_delay);
    if(cur_mouse != 0 ){
        //add mouse key
        if(temp_list.size()>0 && (temp_list[0]->getNormalKeyIndex() !=0 ||  temp_list[0]->getMediaKeyIndex()!=0 || temp_list[0]->getMouseKeyIndex()!=0)){
            //mouse key is single can not be added
            showWarningDialog(tr("Notice"),tr("You can NOT add mouse event to Macro!"));
        }
        else{
            //add to instant ckb and update ui
            my_ckb->setKey(cur_edit_key_no,temp_kv);
        }
    }
    else if(cur_media!=0){
        //add meida key
        if(temp_list.size()>0 && (temp_list[0]->getNormalKeyIndex() !=0 ||  temp_list[0]->getMediaKeyIndex()!=0 || temp_list[0]->getMouseKeyIndex()!=0)){
            //media key is single can not be added
            showWarningDialog(tr("Notice"),tr("You can NOT add meida key to Macro!"));
        }
        else{
            //add to instant ckb and update ui
            my_ckb->setKey(cur_edit_key_no,temp_kv);
        }
    }
    else{
        //add normal key
        //justify whether there is any single key
        if(my_ckb->getCustomKeyByID(cur_edit_key_no)->isMedia()||my_ckb->getCustomKeyByID(cur_edit_key_no)->isMouse()){
            showWarningDialog(tr("Notice"),tr("You can NOT set MEDIA or MOUSE key to Macro!"));
        }
        else{
            //special key justify
            if(my_ckb->getCustomKeyByID(cur_edit_key_no)->getKeyValueList()[0]->getNormalKeyIndex() == 0 \
                    && my_ckb->getCustomKeyByID(cur_edit_key_no)->getKeyValueList()[0]->getSPKeyList().size() > 0 \
                    && my_ckb->getCustomKeyByID(cur_edit_key_no)->getKeyValueList()[0]->getSPKeyList()[0] == 0)
            {
                my_ckb->setKey(cur_edit_key_no,temp_kv);
            }
            else{
                if(my_ckb->checkMacroAddable(cur_edit_key_no)){
                    //update to class
                    my_ckb->appendKey(cur_edit_key_no,temp_kv);
                }
                else{
                    //can not add to macro because of hardware limit
                    showWarningDialog(tr("Notice"),tr("Can NOT add key macro : hardware limitation!"));
                }
            }
        }
    }

    //clear current stat
    painter->getBtn_addkey()->hide();
    cur_key_sp.clear();
    cur_key_normal.clear();
    cur_mouse =0;
    cur_media =0;
    cur_delay =0;
    //untirgger all sp keys
    for(int i = 0;i<8;i++){
        painter->setVkeyUntriggered(table.getSPkeybByindex(i));
    }
    updateUI();
    return true;
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
void updateUI(){
    //update soft keyboard label
    QString temp = "";
    if(!cur_key_sp.isEmpty()){
        temp = table.getKeyString(cur_key_sp[0]);
        for(int i = 1;i<cur_key_sp.size();i++){
            temp += " + " +  table.getKeyString(cur_key_sp[i]);
        }
    }
    if(!cur_key_normal.isEmpty()){
        int i = 0;
        if(temp == ""){
            temp = table.getKeyString(cur_key_normal[0]);
            i++;
        }
        for(;i<cur_key_normal.size();i++){
            temp += " + " +  table.getKeyString(cur_key_normal[i]);
        }
    }
    if(cur_delay!=0){
        //temp = "Delay"+ ui->et_delay->text() +"s"+temp;
        temp = "Delay"+painter->getEt_delay()->text() +"s"+temp;
    }
    // these keys is single
    if(cur_media!=0){
        temp = table.getKeyString(cur_media);
    }
    if(cur_mouse!=0){
        temp = table.getKeyString(cur_mouse);
    }

    //set selector color
    if(cur_edit_key_no != -1){
        //show cur key
        QString str_temp ="";
        QVector<KeyValue*> kvs = my_ckb->getCustomKeyByID(cur_edit_key_no)->getKeyValueList();
        if(!kvs.isEmpty()){
            str_temp = "(" + table.convertKeyValue2QString(kvs[0])+")";
            for(int i =1;i<kvs.size();i++){
                str_temp += " + ("+table.convertKeyValue2QString(kvs[i])+")";
            }
        }
        //set text
        if(temp != ""){
            if(str_temp == "(None)")
                //ui->tv_keyvalue->setText("("+ temp + " + )");
                painter->getMainTextView()->setText("("+ temp + " + )");
            else
                painter->getMainTextView()->setText(str_temp + " + ("+ temp + " + )");
        }
        else
            painter->getMainTextView()->setText(str_temp);
        my_ckb->getButtonByID(cur_edit_key_no)->setStyleSheet("background-color: rgb(255, 100, 100);"); //red for selected
    }

    //set CKB tirrger condition
    for(int i=0;i<my_ckb->getKeynum();i++){
        if(i == cur_edit_key_no)
            continue;
        if(my_ckb->getCustomKeyByID(i)->isMacro())
            ;//style for macro
        else if(my_ckb->getCustomKeyByID(i)->isMedia())
            ;//yellow for media
        else if(my_ckb->getCustomKeyByID(i)->isMouse())
            ; //green for mouse
        else{
            if(my_ckb->getCustomKeyByID(i)->getKeyValueCount()==1
                    && (my_ckb->getCustomKeyByID(i)->getKeyValueList()[0]->getNormalKeyIndex()!=0
                        ||my_ckb->getCustomKeyByID(i)->getKeyValueList()[0]->getSPKeyList()[0]!=0))
                painter->setCKBKeyTriggered(i); //blue for normal
            else
                painter->setCKBKeyUntriggered(i); //none for unset
        }

    }
}
void initUI(QWidget* qw){
    painter = new UIPainter(qw,qw);
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

