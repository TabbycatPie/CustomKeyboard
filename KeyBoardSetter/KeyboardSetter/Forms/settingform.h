#ifndef SETTINGFORM_H
#define SETTINGFORM_H

#include "configform.h"

#include <QWidget>
#include <qtranslator.h>

namespace Ui {
class settingForm;
}

class SettingForm : public QWidget
{
    Q_OBJECT

public:
    explicit SettingForm(ConfigForm *mainwindow,QWidget *parent = nullptr);
    void setLanguageBtnTriggered(int btn_no);
    char cur_lang = 'c';
    char sel_lang = 'c';
    ~SettingForm();

private:
    Ui::settingForm *ui;
    void changeLanguage(char language);
    //Translator
    QTranslator *translator =NULL;

signals:
    void changeConfigFormLanguage(QString language);
};

#endif // SETTINGFORM_H
