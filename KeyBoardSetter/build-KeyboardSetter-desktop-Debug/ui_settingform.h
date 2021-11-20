/********************************************************************************
** Form generated from reading UI file 'settingform.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGFORM_H
#define UI_SETTINGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_settingForm
{
public:
    QLabel *label_12;
    QPushButton *btn_sf_english;
    QPushButton *btn_sf_chinese;
    QPushButton *btn_sf_ok;

    void setupUi(QWidget *settingForm)
    {
        if (settingForm->objectName().isEmpty())
            settingForm->setObjectName(QString::fromUtf8("settingForm"));
        settingForm->resize(350, 200);
        settingForm->setMinimumSize(QSize(350, 200));
        settingForm->setMaximumSize(QSize(350, 200));
        settingForm->setStyleSheet(QString::fromUtf8("background-color:rgb(48, 56, 65);"));
        label_12 = new QLabel(settingForm);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(29, 25, 111, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font.setPointSize(12);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        label_12->setFont(font);
        label_12->setLayoutDirection(Qt::LeftToRight);
        label_12->setStyleSheet(QString::fromUtf8("font: 12pt \"MS Shell Dlg 2\";\n"
"color:rgb(242, 242, 222);"));
        btn_sf_english = new QPushButton(settingForm);
        btn_sf_english->setObjectName(QString::fromUtf8("btn_sf_english"));
        btn_sf_english->setGeometry(QRect(243, 20, 80, 40));
        btn_sf_english->setMinimumSize(QSize(80, 40));
        btn_sf_english->setMaximumSize(QSize(80, 40));
        btn_sf_english->setCursor(QCursor(Qt::PointingHandCursor));
        btn_sf_english->setStyleSheet(QString::fromUtf8("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(188, 181, 0,0), stop:1 rgba(205, 135, 0,0));border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:16px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}\n"
"\n"
"\n"
""));
        btn_sf_chinese = new QPushButton(settingForm);
        btn_sf_chinese->setObjectName(QString::fromUtf8("btn_sf_chinese"));
        btn_sf_chinese->setGeometry(QRect(153, 20, 80, 40));
        btn_sf_chinese->setMinimumSize(QSize(80, 40));
        btn_sf_chinese->setMaximumSize(QSize(80, 40));
        btn_sf_chinese->setCursor(QCursor(Qt::PointingHandCursor));
        btn_sf_chinese->setStyleSheet(QString::fromUtf8("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(188, 181, 0,0), stop:1 rgba(205, 135, 0,0));border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:16px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}\n"
"\n"
"\n"
""));
        btn_sf_ok = new QPushButton(settingForm);
        btn_sf_ok->setObjectName(QString::fromUtf8("btn_sf_ok"));
        btn_sf_ok->setGeometry(QRect(243, 140, 80, 40));
        btn_sf_ok->setMinimumSize(QSize(80, 40));
        btn_sf_ok->setMaximumSize(QSize(80, 40));
        btn_sf_ok->setCursor(QCursor(Qt::PointingHandCursor));
        btn_sf_ok->setStyleSheet(QString::fromUtf8("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(188, 181, 0,0), stop:1 rgba(205, 135, 0,0));border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:16px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}\n"
"\n"
"\n"
""));

        retranslateUi(settingForm);

        QMetaObject::connectSlotsByName(settingForm);
    } // setupUi

    void retranslateUi(QWidget *settingForm)
    {
        settingForm->setWindowTitle(QApplication::translate("settingForm", "Form", nullptr));
        label_12->setText(QApplication::translate("settingForm", "LANGUAGE\357\274\232", nullptr));
        btn_sf_english->setText(QApplication::translate("settingForm", "ENGLISH", nullptr));
        btn_sf_chinese->setText(QApplication::translate("settingForm", "\344\270\255\346\226\207", nullptr));
        btn_sf_ok->setText(QApplication::translate("settingForm", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class settingForm: public Ui_settingForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGFORM_H
