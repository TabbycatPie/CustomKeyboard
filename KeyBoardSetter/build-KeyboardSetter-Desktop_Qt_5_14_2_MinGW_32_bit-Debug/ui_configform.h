/********************************************************************************
** Form generated from reading UI file 'configform.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGFORM_H
#define UI_CONFIGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigForm
{
public:
    QPushButton *searchdevice_btn;
    QPushButton *searchdevice_btn_2;
    QPushButton *searchdevice_btn_3;
    QPushButton *searchdevice_btn_4;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;

    void setupUi(QWidget *ConfigForm)
    {
        if (ConfigForm->objectName().isEmpty())
            ConfigForm->setObjectName(QString::fromUtf8("ConfigForm"));
        ConfigForm->resize(1000, 370);
        ConfigForm->setMinimumSize(QSize(1000, 370));
        ConfigForm->setMaximumSize(QSize(1000, 370));
        ConfigForm->setStyleSheet(QString::fromUtf8("background-color:rgb(48, 56, 65);"));
        searchdevice_btn = new QPushButton(ConfigForm);
        searchdevice_btn->setObjectName(QString::fromUtf8("searchdevice_btn"));
        searchdevice_btn->setGeometry(QRect(860, 30, 120, 40));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(120);
        sizePolicy.setVerticalStretch(50);
        sizePolicy.setHeightForWidth(searchdevice_btn->sizePolicy().hasHeightForWidth());
        searchdevice_btn->setSizePolicy(sizePolicy);
        searchdevice_btn->setMinimumSize(QSize(120, 40));
        searchdevice_btn->setMaximumSize(QSize(120, 40));
        searchdevice_btn->setCursor(QCursor(Qt::PointingHandCursor));
        searchdevice_btn->setStyleSheet(QString::fromUtf8("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(188, 181, 0,0), stop:1 rgba(205, 135, 0,0));border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:16px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(255, 0, 110), stop:1 rgb(177, 0, 98));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(155, 0, 10), stop:1 rgb(77, 0, 0));color:rgb(202, 202,182);}\n"
"\n"
""));
        searchdevice_btn_2 = new QPushButton(ConfigForm);
        searchdevice_btn_2->setObjectName(QString::fromUtf8("searchdevice_btn_2"));
        searchdevice_btn_2->setGeometry(QRect(919, 80, 60, 40));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(searchdevice_btn_2->sizePolicy().hasHeightForWidth());
        searchdevice_btn_2->setSizePolicy(sizePolicy1);
        searchdevice_btn_2->setMinimumSize(QSize(60, 40));
        searchdevice_btn_2->setMaximumSize(QSize(60, 40));
        searchdevice_btn_2->setCursor(QCursor(Qt::PointingHandCursor));
        searchdevice_btn_2->setStyleSheet(QString::fromUtf8("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0,0), stop:1 rgba(0, 0, 0,0));border:1px solid rgb(242, 242, 222);border-top-right-radius:7px;border-bottom-right-radius:7px;padding:2px 4px;font: 5pt \"Microsoft YaHei UI\";font-size:18px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(0, 255, 157), stop:1 rgb(4, 204, 144));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(0, 155, 57), stop:1 rgb(0, 104, 44));color:rgb(202, 202,182);}\n"
"\n"
""));
        searchdevice_btn_3 = new QPushButton(ConfigForm);
        searchdevice_btn_3->setObjectName(QString::fromUtf8("searchdevice_btn_3"));
        searchdevice_btn_3->setGeometry(QRect(860, 80, 60, 40));
        sizePolicy1.setHeightForWidth(searchdevice_btn_3->sizePolicy().hasHeightForWidth());
        searchdevice_btn_3->setSizePolicy(sizePolicy1);
        searchdevice_btn_3->setMinimumSize(QSize(60, 40));
        searchdevice_btn_3->setMaximumSize(QSize(60, 40));
        searchdevice_btn_3->setCursor(QCursor(Qt::PointingHandCursor));
        searchdevice_btn_3->setStyleSheet(QString::fromUtf8("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(188, 181, 0,0), stop:1 rgba(205, 135, 0,0));border:1px solid rgb(242, 242, 222);border-top-left-radius:7px;border-bottom-left-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:18px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(238, 231, 11), stop:1 rgb(255, 185, 7));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(138, 131, 0), stop:1 rgb(155, 85, 0));color:rgb(202, 202,182);}\n"
"\n"
""));
        searchdevice_btn_4 = new QPushButton(ConfigForm);
        searchdevice_btn_4->setObjectName(QString::fromUtf8("searchdevice_btn_4"));
        searchdevice_btn_4->setGeometry(QRect(860, 130, 120, 40));
        searchdevice_btn_4->setMinimumSize(QSize(120, 40));
        searchdevice_btn_4->setMaximumSize(QSize(120, 40));
        searchdevice_btn_4->setCursor(QCursor(Qt::PointingHandCursor));
        searchdevice_btn_4->setStyleSheet(QString::fromUtf8("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(188, 181, 0,0), stop:1 rgba(205, 135, 0,0));border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:16px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}\n"
"\n"
"\n"
""));
        dockWidget = new QDockWidget(ConfigForm);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidget->setGeometry(QRect(-40, 40, 120, 80));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        dockWidget->setWidget(dockWidgetContents);

        retranslateUi(ConfigForm);

        QMetaObject::connectSlotsByName(ConfigForm);
    } // setupUi

    void retranslateUi(QWidget *ConfigForm)
    {
        ConfigForm->setWindowTitle(QCoreApplication::translate("ConfigForm", "Form", nullptr));
        searchdevice_btn->setText(QCoreApplication::translate("ConfigForm", "Download", nullptr));
        searchdevice_btn_2->setText(QCoreApplication::translate("ConfigForm", "Save", nullptr));
        searchdevice_btn_3->setText(QCoreApplication::translate("ConfigForm", "Load", nullptr));
        searchdevice_btn_4->setText(QCoreApplication::translate("ConfigForm", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfigForm: public Ui_ConfigForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGFORM_H
