#ifndef SETTINGFORM_H
#define SETTINGFORM_H

#include "configform.h"

#include <QWidget>

namespace Ui {
class settingForm;
}

class SettingForm : public QWidget
{
    Q_OBJECT

public:
    explicit SettingForm(ConfigForm *mainwindow,QWidget *parent = nullptr);
    ~SettingForm();

private:
    Ui::settingForm *ui;
    int initial_language_index = 0;
};

#endif // SETTINGFORM_H
