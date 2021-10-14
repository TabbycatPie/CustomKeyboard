#ifndef SETTINGFORM_H
#define SETTINGFORM_H

#include <QWidget>

namespace Ui {
class settingForm;
}

class settingForm : public QWidget
{
    Q_OBJECT

public:
    explicit settingForm(QWidget *parent = nullptr);
    ~settingForm();

private:
    Ui::settingForm *ui;
};

#endif // SETTINGFORM_H
