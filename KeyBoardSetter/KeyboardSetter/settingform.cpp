#include "settingform.h"
#include "ui_settingform.h"

settingForm::settingForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settingForm)
{
    ui->setupUi(this);
    //type setting
    setWindowFlags(Qt::WindowStaysOnTopHint|Qt::CustomizeWindowHint|Qt::WindowCloseButtonHint);
}

void changeBtnStyle(QPushButton *btn,bool trigger){
    if(trigger){
        //set btn to triggered
        btn->setStyleSheet("QPushButton{background-color:rgb(138, 146, 155);border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:10px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:rgb(168, 176, 185);}QPushButton:pressed{background-color:rgb(18, 26, 35);color:rgb(202, 202,182);}");
    }else{
        //set btn to normal
        btn->setStyleSheet("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(188, 181, 0,0), stop:1 rgba(205, 135, 0,0));border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:16px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}");
    }
}
void settingForm::setLanguageBtnTriggered(int btn_no)
{
    switch (btn_no) {
        case 1:
            //chinese
            changeBtnStyle(ui->btn_sf_chinese,true);
            changeBtnStyle(ui->btn_sf_english,false);
            break;
        case 2:
            changeBtnStyle(ui->btn_sf_chinese,false);
            changeBtnStyle(ui->btn_sf_english,true);
            break;
        default:
            break;
    }
}

settingForm::~settingForm()
{
    delete ui;
}
