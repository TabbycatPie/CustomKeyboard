#include "configform.h"
#include "ui_configform.h"

#include <QLabel>
#include <qpushbutton.h>

void initUI(QWidget* qw);

ConfigForm::ConfigForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigForm)
{
    ui->setupUi(this);
    initUI(this);
}

ConfigForm::~ConfigForm()
{
    delete ui;
}


void drawCKBbase(int x,int y,int col,int row,int margin,QWidget* qw){
    QLabel *ql = new QLabel(qw);
    ql->setGeometry(x,y,94*col+2*margin,94*row+2*margin);
    ql->setStyleSheet("border-radius:15px;border:3px solid rgb(88, 96, 105);padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:20px;color:rgb(242, 242, 222);background-color:rgb(38, 46, 55);");
}

QPushButton* drawCKBkey(int x,int y,QString text,QWidget* qw){
    QPushButton *btn = new QPushButton(text,qw);
    btn->setGeometry(x,y,90,90);
    btn->clearMask();
    btn->setBackgroundRole(QPalette::Base);
    btn->setStyleSheet("QPushButton{background-color:rgb(48, 56, 65);border:2px solid rgb(88, 96, 105);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:20px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(88, 96, 105);}");
    return btn;
}

void drawCKB(int x,int y,int col,int row,int margin,QWidget* qw){
    drawCKBbase(x,y,col,row,margin,qw);
    QPushButton *btn_temp;
    int num = 1;
    for(int i=0;i<row;i++){
        for(int j =0;j<col;j++){
           btn_temp = drawCKBkey(x+j*94+margin+2,y+i*94+margin+2,QObject::tr("KEY")+QString::number(num),qw);
           num++;
        }
    }
}




void initUI(QWidget* qw){
    int row = 2;
    int col = 2;
    int margin = 10;
    drawCKB(500-(int)((94*col+2*margin)/2),10,col,row,margin,qw);
}
