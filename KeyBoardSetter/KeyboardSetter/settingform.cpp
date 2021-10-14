#include "settingform.h"
#include "ui_settingform.h"

settingForm::settingForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settingForm)
{
    ui->setupUi(this);
}

settingForm::~settingForm()
{
    delete ui;
}
