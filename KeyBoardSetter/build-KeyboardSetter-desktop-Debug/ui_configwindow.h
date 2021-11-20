/********************************************************************************
** Form generated from reading UI file 'configwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGWINDOW_H
#define UI_CONFIGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QLabel *label;
    QPushButton *pushButton_5;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QPushButton *pushButton_15;
    QPushButton *pushButton_17;
    QPushButton *pushButton_18;
    QPushButton *pushButton_16;
    QPushButton *searchdevice_btn_2;
    QPushButton *searchdevice_btn_3;
    QPushButton *searchdevice_btn;
    QPushButton *searchdevice_btn_4;
    QPushButton *searchdevice_btn_6;
    QPushButton *searchdevice_btn_5;
    QPushButton *searchdevice_btn_7;
    QPushButton *pushButton_19;
    QPushButton *pushButton_20;
    QPushButton *pushButton_21;
    QLabel *label_2;
    QTextBrowser *tv_keyvalue;
    QLineEdit *et_delay;
    QPushButton *btn_save;
    QPushButton *btn_save_2;
    QPushButton *searchdevice_btn_8;
    QPushButton *searchdevice_btn_9;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ConfigWindow)
    {
        if (ConfigWindow->objectName().isEmpty())
            ConfigWindow->setObjectName(QString::fromUtf8("ConfigWindow"));
        ConfigWindow->resize(1000, 600);
        ConfigWindow->setMinimumSize(QSize(1000, 600));
        ConfigWindow->setMaximumSize(QSize(1000, 600));
        ConfigWindow->setStyleSheet(QString::fromUtf8("background-color:rgb(48, 56, 65);"));
        centralwidget = new QWidget(ConfigWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(440, 0, 291, 231));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(780, 10, 211, 211));
        label->setStyleSheet(QString::fromUtf8("border-radius:15px;\n"
"border:3px solid rgb(130, 130, 130);\n"
"padding:2px 4px;\n"
"font: 9pt \"Microsoft YaHei UI\";\n"
"font-size:20px;\n"
"color:rgb(242, 242, 222);"));
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(16, 260, 40, 40));
        pushButton_5->setMinimumSize(QSize(40, 40));
        pushButton_5->setMaximumSize(QSize(40, 40));
        pushButton_5->setLayoutDirection(Qt::LeftToRight);
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(138, 146, 155);border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:10px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:rgb(168, 176, 185);}QPushButton:pressed{background-color:rgb(18, 26, 35);color:rgb(202, 202,182);}"));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(890, 20, 90, 90));
        pushButton_2->setMinimumSize(QSize(90, 90));
        pushButton_2->setMaximumSize(QSize(90, 90));
        pushButton_2->setLayoutDirection(Qt::LeftToRight);
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(168, 176, 185);border:2px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:20px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(890, 120, 90, 90));
        pushButton->setMinimumSize(QSize(90, 90));
        pushButton->setMaximumSize(QSize(90, 90));
        pushButton->setLayoutDirection(Qt::LeftToRight);
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton{border:2px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:20px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}\\n\\n"));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(790, 20, 90, 90));
        pushButton_4->setMinimumSize(QSize(90, 90));
        pushButton_4->setMaximumSize(QSize(90, 90));
        pushButton_4->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_4->setLayoutDirection(Qt::LeftToRight);
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton{border:2px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:20px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}\\n\\n"));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(790, 120, 90, 90));
        pushButton_3->setMinimumSize(QSize(90, 90));
        pushButton_3->setMaximumSize(QSize(90, 90));
        pushButton_3->setLayoutDirection(Qt::LeftToRight);
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton{border:2px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:20px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}"));
        pushButton_6 = new QPushButton(centralwidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(142, 260, 40, 40));
        pushButton_6->setMinimumSize(QSize(40, 40));
        pushButton_6->setMaximumSize(QSize(40, 40));
        pushButton_6->setLayoutDirection(Qt::LeftToRight);
        pushButton_6->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(68, 76, 85);border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:10px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:rgb(168, 176, 185);}QPushButton:pressed{background-color:rgb(18, 26, 35);color:rgb(202, 202,182);}"));
        pushButton_7 = new QPushButton(centralwidget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(100, 260, 40, 40));
        pushButton_7->setMinimumSize(QSize(40, 40));
        pushButton_7->setMaximumSize(QSize(40, 40));
        pushButton_7->setLayoutDirection(Qt::LeftToRight);
        pushButton_7->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(68, 76, 85);border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:10px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:rgb(168, 176, 185);}QPushButton:pressed{background-color:rgb(18, 26, 35);color:rgb(202, 202,182);}"));
        pushButton_8 = new QPushButton(centralwidget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(58, 260, 40, 40));
        pushButton_8->setMinimumSize(QSize(40, 40));
        pushButton_8->setMaximumSize(QSize(40, 40));
        pushButton_8->setLayoutDirection(Qt::LeftToRight);
        pushButton_8->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(68, 76, 85);border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:10px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:rgb(168, 176, 185);}QPushButton:pressed{background-color:rgb(18, 26, 35);color:rgb(202, 202,182);}"));
        pushButton_9 = new QPushButton(centralwidget);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(184, 260, 40, 40));
        pushButton_9->setMinimumSize(QSize(40, 40));
        pushButton_9->setMaximumSize(QSize(40, 40));
        pushButton_9->setLayoutDirection(Qt::LeftToRight);
        pushButton_9->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(68, 76, 85);border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:10px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:rgb(168, 176, 185);}QPushButton:pressed{background-color:rgb(18, 26, 35);color:rgb(202, 202,182);}"));
        pushButton_10 = new QPushButton(centralwidget);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setGeometry(QRect(310, 260, 40, 40));
        pushButton_10->setMinimumSize(QSize(40, 40));
        pushButton_10->setMaximumSize(QSize(40, 40));
        pushButton_10->setLayoutDirection(Qt::LeftToRight);
        pushButton_10->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(68, 76, 85);border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:10px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:rgb(168, 176, 185);}QPushButton:pressed{background-color:rgb(18, 26, 35);color:rgb(202, 202,182);}"));
        pushButton_11 = new QPushButton(centralwidget);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setGeometry(QRect(268, 260, 40, 40));
        pushButton_11->setMinimumSize(QSize(40, 40));
        pushButton_11->setMaximumSize(QSize(40, 40));
        pushButton_11->setLayoutDirection(Qt::LeftToRight);
        pushButton_11->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(68, 76, 85);border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:10px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:rgb(168, 176, 185);}QPushButton:pressed{background-color:rgb(18, 26, 35);color:rgb(202, 202,182);}"));
        pushButton_12 = new QPushButton(centralwidget);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        pushButton_12->setGeometry(QRect(226, 260, 40, 40));
        pushButton_12->setMinimumSize(QSize(40, 40));
        pushButton_12->setMaximumSize(QSize(40, 40));
        pushButton_12->setLayoutDirection(Qt::LeftToRight);
        pushButton_12->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(68, 76, 85);border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:10px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:rgb(168, 176, 185);}QPushButton:pressed{background-color:rgb(18, 26, 35);color:rgb(202, 202,182);}"));
        pushButton_13 = new QPushButton(centralwidget);
        pushButton_13->setObjectName(QString::fromUtf8("pushButton_13"));
        pushButton_13->setGeometry(QRect(352, 260, 40, 40));
        pushButton_13->setMinimumSize(QSize(40, 40));
        pushButton_13->setMaximumSize(QSize(40, 40));
        pushButton_13->setLayoutDirection(Qt::LeftToRight);
        pushButton_13->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(68, 76, 85);border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:10px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:rgb(168, 176, 185);}QPushButton:pressed{background-color:rgb(18, 26, 35);color:rgb(202, 202,182);}"));
        pushButton_14 = new QPushButton(centralwidget);
        pushButton_14->setObjectName(QString::fromUtf8("pushButton_14"));
        pushButton_14->setGeometry(QRect(394, 260, 40, 40));
        pushButton_14->setMinimumSize(QSize(40, 40));
        pushButton_14->setMaximumSize(QSize(40, 40));
        pushButton_14->setLayoutDirection(Qt::LeftToRight);
        pushButton_14->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(68, 76, 85);border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:10px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:rgb(168, 176, 185);}QPushButton:pressed{background-color:rgb(18, 26, 35);color:rgb(202, 202,182);}"));
        pushButton_15 = new QPushButton(centralwidget);
        pushButton_15->setObjectName(QString::fromUtf8("pushButton_15"));
        pushButton_15->setGeometry(QRect(436, 260, 40, 40));
        pushButton_15->setMinimumSize(QSize(40, 40));
        pushButton_15->setMaximumSize(QSize(40, 40));
        pushButton_15->setLayoutDirection(Qt::LeftToRight);
        pushButton_15->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(68, 76, 85);border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:10px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:rgb(168, 176, 185);}QPushButton:pressed{background-color:rgb(18, 26, 35);color:rgb(202, 202,182);}"));
        pushButton_17 = new QPushButton(centralwidget);
        pushButton_17->setObjectName(QString::fromUtf8("pushButton_17"));
        pushButton_17->setGeometry(QRect(563, 260, 80, 40));
        pushButton_17->setMinimumSize(QSize(80, 40));
        pushButton_17->setMaximumSize(QSize(40, 40));
        pushButton_17->setLayoutDirection(Qt::LeftToRight);
        pushButton_17->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(68, 76, 85);border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:10px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:rgb(168, 176, 185);}QPushButton:pressed{background-color:rgb(18, 26, 35);color:rgb(202, 202,182);}"));
        pushButton_18 = new QPushButton(centralwidget);
        pushButton_18->setObjectName(QString::fromUtf8("pushButton_18"));
        pushButton_18->setGeometry(QRect(478, 260, 40, 40));
        pushButton_18->setMinimumSize(QSize(40, 40));
        pushButton_18->setMaximumSize(QSize(40, 40));
        pushButton_18->setLayoutDirection(Qt::LeftToRight);
        pushButton_18->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(68, 76, 85);border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:10px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:rgb(168, 176, 185);}QPushButton:pressed{background-color:rgb(18, 26, 35);color:rgb(202, 202,182);}"));
        pushButton_16 = new QPushButton(centralwidget);
        pushButton_16->setObjectName(QString::fromUtf8("pushButton_16"));
        pushButton_16->setGeometry(QRect(520, 260, 40, 40));
        pushButton_16->setMinimumSize(QSize(40, 40));
        pushButton_16->setMaximumSize(QSize(40, 40));
        pushButton_16->setLayoutDirection(Qt::LeftToRight);
        pushButton_16->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(68, 76, 85);border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:10px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:rgb(168, 176, 185);}QPushButton:pressed{background-color:rgb(18, 26, 35);color:rgb(202, 202,182);}"));
        searchdevice_btn_2 = new QPushButton(centralwidget);
        searchdevice_btn_2->setObjectName(QString::fromUtf8("searchdevice_btn_2"));
        searchdevice_btn_2->setGeometry(QRect(359, 60, 60, 50));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(searchdevice_btn_2->sizePolicy().hasHeightForWidth());
        searchdevice_btn_2->setSizePolicy(sizePolicy);
        searchdevice_btn_2->setMinimumSize(QSize(60, 50));
        searchdevice_btn_2->setMaximumSize(QSize(60, 50));
        searchdevice_btn_2->setCursor(QCursor(Qt::PointingHandCursor));
        searchdevice_btn_2->setStyleSheet(QString::fromUtf8("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0,0), stop:1 rgba(0, 0, 0,0));border:1px solid rgb(242, 242, 222);border-top-right-radius:7px;border-bottom-right-radius:7px;padding:2px 4px;font: 5pt \"Microsoft YaHei UI\";font-size:18px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(0, 255, 157), stop:1 rgb(4, 204, 144));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(0, 155, 57), stop:1 rgb(0, 104, 44));color:rgb(202, 202,182);}\n"
"\n"
""));
        searchdevice_btn_3 = new QPushButton(centralwidget);
        searchdevice_btn_3->setObjectName(QString::fromUtf8("searchdevice_btn_3"));
        searchdevice_btn_3->setGeometry(QRect(300, 60, 60, 50));
        sizePolicy.setHeightForWidth(searchdevice_btn_3->sizePolicy().hasHeightForWidth());
        searchdevice_btn_3->setSizePolicy(sizePolicy);
        searchdevice_btn_3->setMinimumSize(QSize(60, 50));
        searchdevice_btn_3->setMaximumSize(QSize(60, 50));
        searchdevice_btn_3->setCursor(QCursor(Qt::PointingHandCursor));
        searchdevice_btn_3->setStyleSheet(QString::fromUtf8("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(188, 181, 0,0), stop:1 rgba(205, 135, 0,0));border:1px solid rgb(242, 242, 222);border-top-left-radius:7px;border-bottom-left-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:18px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(238, 231, 11), stop:1 rgb(255, 185, 7));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(138, 131, 0), stop:1 rgb(155, 85, 0));color:rgb(202, 202,182);}\n"
"\n"
""));
        searchdevice_btn = new QPushButton(centralwidget);
        searchdevice_btn->setObjectName(QString::fromUtf8("searchdevice_btn"));
        searchdevice_btn->setGeometry(QRect(300, 10, 120, 41));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(120);
        sizePolicy1.setVerticalStretch(50);
        sizePolicy1.setHeightForWidth(searchdevice_btn->sizePolicy().hasHeightForWidth());
        searchdevice_btn->setSizePolicy(sizePolicy1);
        searchdevice_btn->setMaximumSize(QSize(120, 50));
        searchdevice_btn->setCursor(QCursor(Qt::PointingHandCursor));
        searchdevice_btn->setStyleSheet(QString::fromUtf8("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(188, 181, 0,0), stop:1 rgba(205, 135, 0,0));border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:16px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(238, 231, 11), stop:1 rgb(255, 185, 7));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(138, 131, 0), stop:1 rgb(155, 85, 0));color:rgb(202, 202,182);}\n"
"\n"
""));
        searchdevice_btn_4 = new QPushButton(centralwidget);
        searchdevice_btn_4->setObjectName(QString::fromUtf8("searchdevice_btn_4"));
        searchdevice_btn_4->setGeometry(QRect(300, 120, 120, 50));
        searchdevice_btn_4->setMinimumSize(QSize(120, 50));
        searchdevice_btn_4->setMaximumSize(QSize(120, 50));
        searchdevice_btn_4->setCursor(QCursor(Qt::PointingHandCursor));
        searchdevice_btn_4->setStyleSheet(QString::fromUtf8("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(188, 181, 0,0), stop:1 rgba(205, 135, 0,0));border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:16px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}\n"
"\n"
""));
        searchdevice_btn_6 = new QPushButton(centralwidget);
        searchdevice_btn_6->setObjectName(QString::fromUtf8("searchdevice_btn_6"));
        searchdevice_btn_6->setGeometry(QRect(31, 20, 80, 20));
        sizePolicy.setHeightForWidth(searchdevice_btn_6->sizePolicy().hasHeightForWidth());
        searchdevice_btn_6->setSizePolicy(sizePolicy);
        searchdevice_btn_6->setMinimumSize(QSize(80, 20));
        searchdevice_btn_6->setMaximumSize(QSize(80, 20));
        searchdevice_btn_6->setCursor(QCursor(Qt::PointingHandCursor));
        searchdevice_btn_6->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(138, 146, 155);border:1px solid rgb(242, 242, 222);border-top-left-radius:7px;border-bottom-left-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";color:rgb(242, 242, 222);font-size:12px;}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}\n"
""));
        searchdevice_btn_5 = new QPushButton(centralwidget);
        searchdevice_btn_5->setObjectName(QString::fromUtf8("searchdevice_btn_5"));
        searchdevice_btn_5->setGeometry(QRect(169, 20, 75, 20));
        sizePolicy.setHeightForWidth(searchdevice_btn_5->sizePolicy().hasHeightForWidth());
        searchdevice_btn_5->setSizePolicy(sizePolicy);
        searchdevice_btn_5->setMinimumSize(QSize(75, 20));
        searchdevice_btn_5->setMaximumSize(QSize(75, 20));
        searchdevice_btn_5->setCursor(QCursor(Qt::PointingHandCursor));
        searchdevice_btn_5->setStyleSheet(QString::fromUtf8("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0,0), stop:1 rgba(0, 0, 0,0));border:1px solid rgb(242, 242, 222);border-top-right-radius:7px;border-bottom-right-radius:7px;padding:2px 4px;font: 5pt \"Microsoft YaHei UI\";font-size:12px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}\n"
""));
        searchdevice_btn_7 = new QPushButton(centralwidget);
        searchdevice_btn_7->setObjectName(QString::fromUtf8("searchdevice_btn_7"));
        searchdevice_btn_7->setGeometry(QRect(110, 20, 60, 20));
        sizePolicy.setHeightForWidth(searchdevice_btn_7->sizePolicy().hasHeightForWidth());
        searchdevice_btn_7->setSizePolicy(sizePolicy);
        searchdevice_btn_7->setMinimumSize(QSize(60, 20));
        searchdevice_btn_7->setMaximumSize(QSize(60, 20));
        searchdevice_btn_7->setCursor(QCursor(Qt::PointingHandCursor));
        searchdevice_btn_7->setStyleSheet(QString::fromUtf8("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0,0), stop:1 rgba(0, 0, 0,0));border:1px solid rgb(242, 242, 222);padding:2px 4px;font: 5pt \"Microsoft YaHei UI\";font-size:12px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}\n"
""));
        pushButton_19 = new QPushButton(centralwidget);
        pushButton_19->setObjectName(QString::fromUtf8("pushButton_19"));
        pushButton_19->setGeometry(QRect(40, 65, 40, 70));
        pushButton_19->setMinimumSize(QSize(40, 70));
        pushButton_19->setMaximumSize(QSize(40, 70));
        pushButton_19->setLayoutDirection(Qt::LeftToRight);
        pushButton_19->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(68, 76, 85);border:1px solid rgb(242, 242, 222);border-radius:7px;border-top-left-radius:30px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:10px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:rgb(168, 176, 185);}QPushButton:pressed{background-color:rgb(18, 26, 35);color:rgb(202, 202,182);}"));
        pushButton_20 = new QPushButton(centralwidget);
        pushButton_20->setObjectName(QString::fromUtf8("pushButton_20"));
        pushButton_20->setGeometry(QRect(95, 65, 40, 70));
        pushButton_20->setMinimumSize(QSize(40, 70));
        pushButton_20->setMaximumSize(QSize(40, 70));
        pushButton_20->setLayoutDirection(Qt::LeftToRight);
        pushButton_20->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(68, 76, 85);border:1px solid rgb(242, 242, 222);border-radius:7px;border-top-right-radius:30px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:10px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:rgb(168, 176, 185);}QPushButton:pressed{background-color:rgb(18, 26, 35);color:rgb(202, 202,182);}"));
        pushButton_21 = new QPushButton(centralwidget);
        pushButton_21->setObjectName(QString::fromUtf8("pushButton_21"));
        pushButton_21->setGeometry(QRect(80, 80, 15, 40));
        pushButton_21->setMinimumSize(QSize(15, 40));
        pushButton_21->setMaximumSize(QSize(15, 40));
        pushButton_21->setLayoutDirection(Qt::LeftToRight);
        pushButton_21->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(68, 76, 85);border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:10px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:rgb(168, 176, 185);}QPushButton:pressed{background-color:rgb(18, 26, 35);color:rgb(202, 202,182);}"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 139, 95, 95));
        label_2->setMinimumSize(QSize(95, 95));
        label_2->setMaximumSize(QSize(95, 95));
        label_2->setStyleSheet(QString::fromUtf8("background-color:rgb(68, 76, 85);border:1px solid rgb(242, 242, 222);border-radius:7px;border-bottom-right-radius:40px;border-bottom-left-radius:40px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:10px;color:rgb(242, 242, 222);"));
        tv_keyvalue = new QTextBrowser(centralwidget);
        tv_keyvalue->setObjectName(QString::fromUtf8("tv_keyvalue"));
        tv_keyvalue->setGeometry(QRect(11, 310, 850, 60));
        tv_keyvalue->setMinimumSize(QSize(850, 60));
        tv_keyvalue->setMaximumSize(QSize(850, 60));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        tv_keyvalue->setFont(font);
        tv_keyvalue->setStyleSheet(QString::fromUtf8("background-color:rgba(168, 176, 185,0);border:1px solid rgb(242, 242, 222);padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:20px;color:rgb(242, 242, 222);border-top-left-radius:7px;border-bottom-left-radius:7px;"));
        tv_keyvalue->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tv_keyvalue->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        et_delay = new QLineEdit(centralwidget);
        et_delay->setObjectName(QString::fromUtf8("et_delay"));
        et_delay->setGeometry(QRect(651, 261, 60, 39));
        et_delay->setMinimumSize(QSize(60, 39));
        et_delay->setMaximumSize(QSize(60, 39));
        et_delay->setStyleSheet(QString::fromUtf8("background-color:rgb(68, 76, 85);\n"
"border:1px solid rgb(242, 242, 222);\n"
"border-top-left-radius:7px;\n"
"border-bottom-left-radius:7px;\n"
"padding:2px 4px;\n"
"font: 9pt \"Microsoft YaHei UI\";\n"
"font-size:15px;\n"
"color:rgb(242, 242, 222);"));
        btn_save = new QPushButton(centralwidget);
        btn_save->setObjectName(QString::fromUtf8("btn_save"));
        btn_save->setGeometry(QRect(710, 261, 30, 20));
        sizePolicy.setHeightForWidth(btn_save->sizePolicy().hasHeightForWidth());
        btn_save->setSizePolicy(sizePolicy);
        btn_save->setMinimumSize(QSize(30, 20));
        btn_save->setMaximumSize(QSize(30, 20));
        btn_save->setCursor(QCursor(Qt::PointingHandCursor));
        btn_save->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(68, 76, 85);border:1px solid rgb(242, 242, 222);border-top-right-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:10px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:rgb(168, 176, 185);}QPushButton:pressed{background-color:rgb(18, 26, 35);color:rgb(202, 202,182);}"));
        btn_save_2 = new QPushButton(centralwidget);
        btn_save_2->setObjectName(QString::fromUtf8("btn_save_2"));
        btn_save_2->setGeometry(QRect(710, 280, 30, 20));
        sizePolicy.setHeightForWidth(btn_save_2->sizePolicy().hasHeightForWidth());
        btn_save_2->setSizePolicy(sizePolicy);
        btn_save_2->setMinimumSize(QSize(30, 20));
        btn_save_2->setMaximumSize(QSize(30, 20));
        btn_save_2->setCursor(QCursor(Qt::PointingHandCursor));
        btn_save_2->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(68, 76, 85);border:1px solid rgb(242, 242, 222);border-bottom-right-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:10px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:rgb(168, 176, 185);}QPushButton:pressed{background-color:rgb(18, 26, 35);color:rgb(202, 202,182);}"));
        searchdevice_btn_8 = new QPushButton(centralwidget);
        searchdevice_btn_8->setObjectName(QString::fromUtf8("searchdevice_btn_8"));
        searchdevice_btn_8->setGeometry(QRect(860, 380, 100, 60));
        sizePolicy.setHeightForWidth(searchdevice_btn_8->sizePolicy().hasHeightForWidth());
        searchdevice_btn_8->setSizePolicy(sizePolicy);
        searchdevice_btn_8->setMinimumSize(QSize(100, 60));
        searchdevice_btn_8->setMaximumSize(QSize(100, 60));
        searchdevice_btn_8->setCursor(QCursor(Qt::PointingHandCursor));
        searchdevice_btn_8->setStyleSheet(QString::fromUtf8("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0,0), stop:1 rgba(0, 0, 0,0));border:1px solid rgb(242, 242, 222);border-top-right-radius:7px;border-bottom-right-radius:7px;padding:2px 4px;font: 5pt \"Microsoft YaHei UI\";font-size:18px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(0, 255, 157), stop:1 rgb(4, 204, 144));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(0, 155, 57), stop:1 rgb(0, 104, 44));color:rgb(202, 202,182);}\n"
"\n"
""));
        searchdevice_btn_9 = new QPushButton(centralwidget);
        searchdevice_btn_9->setObjectName(QString::fromUtf8("searchdevice_btn_9"));
        searchdevice_btn_9->setGeometry(QRect(860, 310, 100, 60));
        sizePolicy.setHeightForWidth(searchdevice_btn_9->sizePolicy().hasHeightForWidth());
        searchdevice_btn_9->setSizePolicy(sizePolicy);
        searchdevice_btn_9->setMinimumSize(QSize(100, 60));
        searchdevice_btn_9->setMaximumSize(QSize(100, 60));
        searchdevice_btn_9->setCursor(QCursor(Qt::PointingHandCursor));
        searchdevice_btn_9->setStyleSheet(QString::fromUtf8("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0,0), stop:1 rgba(0, 0, 0,0));border:1px solid rgb(242, 242, 222);border-top-right-radius:7px;border-bottom-right-radius:7px;padding:2px 4px;font: 5pt \"Microsoft YaHei UI\";font-size:18px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(255, 0, 157), stop:1 rgb(204, 4, 144));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(205, 0, 107), stop:1 rgb(154, 4, 94));color:rgb(202, 202,182);}\n"
"\n"
""));
        ConfigWindow->setCentralWidget(centralwidget);
        label_2->raise();
        label->raise();
        groupBox->raise();
        pushButton_5->raise();
        pushButton_2->raise();
        pushButton->raise();
        pushButton_4->raise();
        pushButton_3->raise();
        pushButton_6->raise();
        pushButton_7->raise();
        pushButton_8->raise();
        pushButton_9->raise();
        pushButton_10->raise();
        pushButton_11->raise();
        pushButton_12->raise();
        pushButton_13->raise();
        pushButton_14->raise();
        pushButton_15->raise();
        pushButton_17->raise();
        pushButton_18->raise();
        pushButton_16->raise();
        searchdevice_btn_2->raise();
        searchdevice_btn_3->raise();
        searchdevice_btn->raise();
        searchdevice_btn_4->raise();
        searchdevice_btn_6->raise();
        searchdevice_btn_5->raise();
        searchdevice_btn_7->raise();
        pushButton_19->raise();
        pushButton_20->raise();
        pushButton_21->raise();
        tv_keyvalue->raise();
        et_delay->raise();
        btn_save->raise();
        btn_save_2->raise();
        searchdevice_btn_8->raise();
        searchdevice_btn_9->raise();
        menubar = new QMenuBar(ConfigWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1000, 30));
        ConfigWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ConfigWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ConfigWindow->setStatusBar(statusbar);

        retranslateUi(ConfigWindow);

        QMetaObject::connectSlotsByName(ConfigWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ConfigWindow)
    {
        ConfigWindow->setWindowTitle(QApplication::translate("ConfigWindow", "MainWindow", nullptr));
        groupBox->setTitle(QApplication::translate("ConfigWindow", "Device information:", nullptr));
        label->setText(QString());
        pushButton_5->setText(QApplication::translate("ConfigWindow", "`~", nullptr));
        pushButton_2->setText(QApplication::translate("ConfigWindow", "KEY1", nullptr));
        pushButton->setText(QApplication::translate("ConfigWindow", "KEY1", nullptr));
        pushButton_4->setText(QApplication::translate("ConfigWindow", "KEY1", nullptr));
        pushButton_3->setText(QApplication::translate("ConfigWindow", "KEY1", nullptr));
        pushButton_6->setText(QApplication::translate("ConfigWindow", "3#", nullptr));
        pushButton_7->setText(QApplication::translate("ConfigWindow", "2@", nullptr));
        pushButton_8->setText(QApplication::translate("ConfigWindow", "1!", nullptr));
        pushButton_9->setText(QApplication::translate("ConfigWindow", "4$", nullptr));
        pushButton_10->setText(QApplication::translate("ConfigWindow", "7&&", nullptr));
        pushButton_11->setText(QApplication::translate("ConfigWindow", "6^", nullptr));
        pushButton_12->setText(QApplication::translate("ConfigWindow", "5%", nullptr));
        pushButton_13->setText(QApplication::translate("ConfigWindow", "8*", nullptr));
        pushButton_14->setText(QApplication::translate("ConfigWindow", "9(", nullptr));
        pushButton_15->setText(QApplication::translate("ConfigWindow", "0)", nullptr));
        pushButton_17->setText(QApplication::translate("ConfigWindow", "Backspace", nullptr));
        pushButton_18->setText(QApplication::translate("ConfigWindow", "-", nullptr));
        pushButton_16->setText(QApplication::translate("ConfigWindow", "=+", nullptr));
        searchdevice_btn_2->setText(QApplication::translate("ConfigWindow", "Save", nullptr));
        searchdevice_btn_3->setText(QApplication::translate("ConfigWindow", "Load", nullptr));
        searchdevice_btn->setText(QApplication::translate("ConfigWindow", "Download", nullptr));
        searchdevice_btn_4->setText(QApplication::translate("ConfigWindow", "Settings", nullptr));
        searchdevice_btn_6->setText(QApplication::translate("ConfigWindow", "KEYBOARD", nullptr));
        searchdevice_btn_5->setText(QApplication::translate("ConfigWindow", "ADVANCE", nullptr));
        searchdevice_btn_7->setText(QApplication::translate("ConfigWindow", "MOUSE", nullptr));
        pushButton_19->setText(QString());
        pushButton_20->setText(QString());
        pushButton_21->setText(QString());
        label_2->setText(QString());
        tv_keyvalue->setHtml(QApplication::translate("ConfigWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:20px; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20px;\">helloworld</span></p></body></html>", nullptr));
        et_delay->setText(QApplication::translate("ConfigWindow", "0.0", nullptr));
        btn_save->setText(QApplication::translate("ConfigWindow", "+", nullptr));
        btn_save_2->setText(QApplication::translate("ConfigWindow", "-", nullptr));
        searchdevice_btn_8->setText(QApplication::translate("ConfigWindow", "ADD", nullptr));
        searchdevice_btn_9->setText(QApplication::translate("ConfigWindow", "DELETE", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfigWindow: public Ui_ConfigWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGWINDOW_H
