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

    //while(true){
    //    version = ckb[0]->getVersion();
    //    if(version<0){
    //        QMessageBox msg_info(this);
    //        msg_info.setWindowTitle(tr("Notice"));
    //        msg_info.setText(tr("Device not found,please connect then press ok."));
    //        msg_info.setIcon(QMessageBox::Information);
    //        msg_info.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    //        if(msg_info.exec()==QMessageBox::Cancel){
    //            break;
    //        }
    //    }else
    //        break;
    //}

    connect(ui->searchdevice_btn,&QPushButton::clicked,this,[=]{
        //ui change
        ui->main_label->setText(tr(" Searching ... "));
        ui->sub_label->setText("");
        ui->main_label->repaint();
        ui->sub_label->repaint();
        QThread::msleep(300);
        //justify wether the device is pluged in
        if(CustomKeyboard("tryopen",0,0x2019,0x5131,nullptr).tryOpen()){
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

void DeviceFinder::setMw(MainWindow* mainwindow){
    this->mw = mainwindow;
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
    this->mw->show();
    this->mw->initData(translator);
    this->close();
}


