#include "configform.h"
#include "ui_configform.h"
#include "uipainter.h"

#include <QLabel>
#include <qpushbutton.h>

void initUI(QWidget* qw);

ConfigForm::ConfigForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigForm)
{
    ui->setupUi(this);
    //initUI(this);
    int row = 2;
    int col = 5;
    UIPainter *painter = new UIPainter(this,this);
    painter->drawCKB(450-(int)(painter->getCKBWigth(col)/2),painter->getUI_part_margin(),col,row);

    painter->drawOutputPort(painter->getUI_part_margin(),painter->getCKBHeight(row)+50);

    painter->drawSwitch(painter->getUI_part_margin(),painter->getCKBHeight(row)+painter->getPortHeight()+55);

    painter->drawVKBfull(painter->getUI_part_margin(),painter->getCKBHeight(row)+painter->getPortHeight()+80);

    //test show_only_mouse
    //painter->hideVKB();
    painter->drawVMouse(painter->getUI_part_margin(),painter->getCKBHeight(row)+painter->getPortHeight()+80);
    painter->hideVMouse();

    QVector<QPushButton*> *temp = painter->getSW_list();

    connect(temp->data()[0],&QPushButton::clicked,this,[=]{
        painter->switchVinput(painter->VKEYBOARD);
    });
    connect(temp->data()[1],&QPushButton::clicked,this,[=]{
        painter->switchVinput(painter->VMOUSE);
    });
    connect(temp->data()[2],&QPushButton::clicked,this,[=]{
        painter->switchVinput(painter->VADVANCE);
    });
    painter->triggerSwitch(0);

    this->setFixedSize(1000,painter->getFullWindowHeight(row));
}

ConfigForm::~ConfigForm()
{
    delete ui;
}


void initUI(QWidget* qw){
//    int row = 2;
//    int col = 5;
//    int margin = 10;
//    UIPainter painter = new UIPainter(ui,this)
 //   drawCKB(450-(int)((94*col+2*margin)/2),10,col,row,margin,qw);
}
