#include "Utils/configsaver.h"
#include "settingform.h"
#include "ui_settingform.h"
#include "Utils/userconfig.h"
#include "configform.h"
#include <qjsonobject.h>
#include <QDebug>
#include <QMessageBox>

SettingForm::SettingForm(ConfigForm *mainwindow,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settingForm)
{
    ui->setupUi(this);


    //load from config
    ConfigSaver cs;
    QString filename =  QCoreApplication::applicationDirPath() + "//usercondif.ini";
    QJsonObject *jsonobj = new QJsonObject();
    if(!cs.readConfig(filename,jsonobj))
        qDebug() << "Can not read userconfig.ini";
    UserConfig *uc = UserConfig::fromJson(*jsonobj);
    if(uc->getLanguage()=="english"){
        changeLanguage('e');
        this->cur_lang = 'e';
    }else{
        changeLanguage('c');
        this->cur_lang = 'c';
    }
    //type setting
    setWindowFlags(Qt::Window|Qt::WindowStaysOnTopHint|Qt::CustomizeWindowHint|Qt::WindowCloseButtonHint);

    this->setWindowTitle(tr("Menu"));

    ui->cb_modifier_delay->setCurrentIndex(mainwindow->getModifierDelayLevel());

    //connect functions
    connect(ui->btn_sf_load,&QPushButton::clicked,mainwindow,&ConfigForm::loadConfigFromMenu);
    connect(ui->btn_sf_save,&QPushButton::clicked,mainwindow,&ConfigForm::saveConfigFromMenu);
    connect(ui->cb_modifier_delay,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),mainwindow,&ConfigForm::setModifierDelayLevel);
    connect(ui->btn_sf_ok,&QPushButton::clicked,this,[=]{
        //notice user to restart
        if(cur_lang!=sel_lang){
            //if there is a language changing
            QMessageBox msg_info(this);
            msg_info.setStyleSheet("color:rgb(242, 242, 222);");
            msg_info.setWindowTitle(tr("Notice"));
            msg_info.setText(tr("A Restart is needed to apply language changing."));
            msg_info.setIcon(QMessageBox::Information);
            msg_info.setStandardButtons(QMessageBox::Ok);
            msg_info.exec();
        }
        this->close();
    });
    connect(ui->btn_sf_chinese,&QPushButton::clicked,this,[=]{
        changeLanguage('c');
        this->sel_lang = 'c';
        mainwindow->changeLanguage("cn");
    });
    connect(ui->btn_sf_english,&QPushButton::clicked,this,[=]{
        changeLanguage('e');
        this->sel_lang = 'e';
        mainwindow->changeLanguage("en");
    });
}

void changeBtnStyle(QPushButton *btn,bool trigger){
    if(trigger){
        //set btn to triggered
        btn->setStyleSheet("QPushButton{background-color:rgb(138, 146, 155);border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";color:rgb(242, 242, 222);}QPushButton:hover{background-color:rgb(168, 176, 185);}QPushButton:pressed{background-color:rgb(18, 26, 35);color:rgb(202, 202,182);}");
    }else{
        //set btn to normal
        btn->setStyleSheet("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(188, 181, 0,0), stop:1 rgba(205, 135, 0,0));border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:16px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}");
    }
}
void SettingForm::setLanguageBtnTriggered(int btn_no)
{
    switch (btn_no) {
        case 1:
            //chinese
            changeBtnStyle(ui->btn_sf_chinese,true);
            changeBtnStyle(ui->btn_sf_english,false);
            break;
        case 2:
            changeBtnStyle(ui->btn_sf_chinese,false);
            changeBtnStyle(ui->btn_sf_english,true);
            break;
        default:
            break;
    }
}
void SettingForm::changeLanguage(char language){
    switch (language) {
    case 'c':
        setLanguageBtnTriggered(1);
        break;
    case 'e':
        setLanguageBtnTriggered(2);
        break;
    default:
        break;
    }
}

SettingForm::~SettingForm()
{
    delete ui;
}
