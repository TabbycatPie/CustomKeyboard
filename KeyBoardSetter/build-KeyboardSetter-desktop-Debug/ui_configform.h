/********************************************************************************
** Form generated from reading UI file 'configform.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGFORM_H
#define UI_CONFIGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigForm
{
public:
    QPushButton *btn_download;
    QPushButton *btn_save;
    QPushButton *btn_load;
    QPushButton *btn_settings;

    void setupUi(QWidget *ConfigForm)
    {
        if (ConfigForm->objectName().isEmpty())
            ConfigForm->setObjectName(QString::fromUtf8("ConfigForm"));
        ConfigForm->resize(1000, 370);
        ConfigForm->setMinimumSize(QSize(1000, 370));
        ConfigForm->setMaximumSize(QSize(1000, 370));
        ConfigForm->setStyleSheet(QString::fromUtf8("background-color:rgb(48, 56, 65);"));
        btn_download = new QPushButton(ConfigForm);
        btn_download->setObjectName(QString::fromUtf8("btn_download"));
        btn_download->setGeometry(QRect(860, 35, 120, 40));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(120);
        sizePolicy.setVerticalStretch(50);
        sizePolicy.setHeightForWidth(btn_download->sizePolicy().hasHeightForWidth());
        btn_download->setSizePolicy(sizePolicy);
        btn_download->setMinimumSize(QSize(120, 40));
        btn_download->setMaximumSize(QSize(120, 40));
        btn_download->setCursor(QCursor(Qt::PointingHandCursor));
        btn_download->setStyleSheet(QString::fromUtf8("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(188, 181, 0,0), stop:1 rgba(205, 135, 0,0));border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:16px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(255, 0, 110), stop:1 rgb(177, 0, 98));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(155, 0, 10), stop:1 rgb(77, 0, 0));color:rgb(202, 202,182);}\n"
"\n"
""));
        btn_save = new QPushButton(ConfigForm);
        btn_save->setObjectName(QString::fromUtf8("btn_save"));
        btn_save->setGeometry(QRect(919, 80, 60, 40));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btn_save->sizePolicy().hasHeightForWidth());
        btn_save->setSizePolicy(sizePolicy1);
        btn_save->setMinimumSize(QSize(60, 40));
        btn_save->setMaximumSize(QSize(60, 40));
        btn_save->setCursor(QCursor(Qt::PointingHandCursor));
        btn_save->setStyleSheet(QString::fromUtf8("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0,0), stop:1 rgba(0, 0, 0,0));border:1px solid rgb(242, 242, 222);border-top-right-radius:7px;border-bottom-right-radius:7px;padding:2px 4px;font: 5pt \"Microsoft YaHei UI\";font-size:18px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}\n"
""));
        btn_load = new QPushButton(ConfigForm);
        btn_load->setObjectName(QString::fromUtf8("btn_load"));
        btn_load->setGeometry(QRect(860, 80, 60, 40));
        sizePolicy1.setHeightForWidth(btn_load->sizePolicy().hasHeightForWidth());
        btn_load->setSizePolicy(sizePolicy1);
        btn_load->setMinimumSize(QSize(60, 40));
        btn_load->setMaximumSize(QSize(60, 40));
        btn_load->setCursor(QCursor(Qt::PointingHandCursor));
        btn_load->setStyleSheet(QString::fromUtf8("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(188, 181, 0,0), stop:1 rgba(205, 135, 0,0));border:1px solid rgb(242, 242, 222);border-top-left-radius:7px;border-bottom-left-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:18px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}\n"
""));
        btn_settings = new QPushButton(ConfigForm);
        btn_settings->setObjectName(QString::fromUtf8("btn_settings"));
        btn_settings->setGeometry(QRect(860, 125, 120, 40));
        btn_settings->setMinimumSize(QSize(120, 40));
        btn_settings->setMaximumSize(QSize(120, 40));
        btn_settings->setCursor(QCursor(Qt::PointingHandCursor));
        btn_settings->setStyleSheet(QString::fromUtf8("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(188, 181, 0,0), stop:1 rgba(205, 135, 0,0));border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:16px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}\n"
"\n"
"\n"
""));

        retranslateUi(ConfigForm);

        QMetaObject::connectSlotsByName(ConfigForm);
    } // setupUi

    void retranslateUi(QWidget *ConfigForm)
    {
        ConfigForm->setWindowTitle(QApplication::translate("ConfigForm", "Form", nullptr));
        btn_download->setText(QApplication::translate("ConfigForm", "Download", nullptr));
        btn_save->setText(QApplication::translate("ConfigForm", "Save", nullptr));
        btn_load->setText(QApplication::translate("ConfigForm", "Load", nullptr));
        btn_settings->setText(QApplication::translate("ConfigForm", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfigForm: public Ui_ConfigForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGFORM_H
