#include "Utils/configsaver.h"
#include "settingform.h"
#include "ui_settingform.h"
#include "Utils/userconfig.h"
#include "configform.h"
#include <qjsonobject.h>
#include <QDebug>
#include <QMessageBox>
#include <QSignalBlocker>

SettingForm::SettingForm(ConfigForm *mainwindow,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settingForm)
{
    ui->setupUi(this);

    ConfigSaver cs;
    QString filename = QCoreApplication::applicationDirPath() + "//usercondif.ini";
    QJsonObject jsonobj;
    if(!cs.readConfig(filename,&jsonobj))
        qDebug() << "Can not read userconfig.ini";
    UserConfig *uc = UserConfig::fromJson(jsonobj);
    initial_language_index = uc->getLanguage()=="english" ? 1 : 0;
    delete uc;

    QSignalBlocker blocker(ui->cb_language);
    ui->cb_language->setCurrentIndex(initial_language_index);

    setWindowFlags(Qt::Window|Qt::CustomizeWindowHint|Qt::WindowCloseButtonHint);
    setWindowTitle(tr("Settings"));

    ui->cb_modifier_delay->setCurrentIndex(mainwindow->getModifierDelayLevel());

    connect(ui->btn_sf_load,&QPushButton::clicked,mainwindow,&ConfigForm::loadConfigFromMenu);
    connect(ui->btn_sf_save,&QPushButton::clicked,mainwindow,&ConfigForm::saveConfigFromMenu);
    connect(ui->cb_modifier_delay,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),mainwindow,&ConfigForm::setModifierDelayLevel);
    connect(ui->btn_sf_ok,&QPushButton::clicked,this,[=]{
        int selected_language_index = ui->cb_language->currentIndex();
        if(selected_language_index != initial_language_index &&
                !mainwindow->changeLanguage(selected_language_index == 0 ? "cn" : "en")){
            QMessageBox *msg_info = new QMessageBox(QMessageBox::Information,
                                                     tr("Notice"),
                                                     tr("Switching language requires reopening the application."),
                                                     QMessageBox::Ok,
                                                     mainwindow);
            msg_info->setStyleSheet("QMessageBox{background-color:rgb(48,56,65);color:rgb(242,242,222);} QLabel{color:rgb(242,242,222);}");
            msg_info->setAttribute(Qt::WA_DeleteOnClose);
            msg_info->setWindowModality(Qt::WindowModal);
            msg_info->show();
        }
        close();
    });
}

SettingForm::~SettingForm()
{
    delete ui;
}
