#include "configwindow.h"
#include "ui_configwindow.h"

//-------public definetion-------------
void initUI();

ConfigWindow::ConfigWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfigWindow)
{
    ui->setupUi(this);
    initUI();
}

ConfigWindow::~ConfigWindow()
{
    delete ui;
}


void drawCKBbase(int x,int y,int col,int row){

}

QPushButton* drawCKBkey(int x,int y,QString text){
    QPushButton *btn = new QPushButton(text);
    btn->setGeometry(x,y,90,90);
    btn->clearMask();
    btn->setBackgroundRole(QPalette::Base);
    //btn->setStyleSheet("QPushButton{border:2px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:20px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}");
    return btn;
}

void drawCKB(int col,int row){
    drawCKBbase(0,1,1,1);
}




void initUI(){
    drawCKBkey(10,10,"KEY1");
    drawCKBkey(105,10,"KEY2");
}
