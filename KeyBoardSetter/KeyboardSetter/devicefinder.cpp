#include "configsaver.h"
#include "devicefinder.h"
#include "ui_devicefinder.h"
#include "userconfig.h"

#include <qaction.h>
#include <qdebug.h>
#include <qthread.h>
#include <qtranslator.h>


//Translator
QTranslator *translator;

DeviceFinder::DeviceFinder(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeviceFinder)
{
    ui->setupUi(this);
    //translator
    //inti translator
    translator = new QTranslator();

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

    //if the device is plugged in open main window
    if(CustomKeyboard(0x2019,0x5131).tryOpen()){
        this->showable = false;
        openMainWindow();
    }

    //developer skip button
    connect(ui->btn_skip,&QPushButton::clicked,this,[=]{
        openMainWindow();
    });


    connect(ui->searchdevice_btn,&QPushButton::clicked,this,[=]{
        //ui change
        ui->main_label->setText(tr(" Searching ... "));
        ui->sub_label->setText("");
        ui->main_label->repaint();
        ui->sub_label->repaint();
        QThread::msleep(300);
        //justify wether the device is pluged in
        if(CustomKeyboard(0x2019,0x5131).tryOpen()){
            ui->main_label->setText(tr(" Device found! "));
            ui->sub_label->setText(tr(""));
            ui->main_label->repaint();
            ui->sub_label->repaint();
            QThread::msleep(300);
            openMainWindow();
        }else{
            ui->main_label->setText(tr(" Device not found! "));
            ui->sub_label->setText(tr("please pulgin your device"));
        }
    });
}

DeviceFinder::~DeviceFinder(){
    delete ui;
}

void DeviceFinder::setMw(ConfigForm* mainwindow){
    this->mw = mainwindow;
}

void DeviceFinder::smartShow()
{
    if(this->showable)
        this->show();
}

void DeviceFinder::changeLanguage(QString language){
    if(language=="cn"){
        QString path = QCoreApplication::applicationDirPath() + "//trans_zh_CN.qm";
        translator->load(path);
        if(qApp->installTranslator(translator)){
            ui->retranslateUi(this);   //refresh ui
        }
        else{
            qDebug() << "Can not load UI language.";
            //logUpdate("Can not load UI language.");
        }
    }else if(language=="en"){
        QString path = QCoreApplication::applicationDirPath() + "//trans_en_US.qm";
        translator->load(path);
        qApp->installTranslator(translator);
        ui->retranslateUi(this);    //refresh ui
        qDebug() << "Using english as UI language.";
        //logUpdate("Using english as UI language.");
    }


}

void DeviceFinder::openMainWindow(){
    setMw(new ConfigForm());
    this->mw->show();
    this->close();
}


