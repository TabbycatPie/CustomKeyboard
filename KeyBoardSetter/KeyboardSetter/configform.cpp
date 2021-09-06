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
    painter->drawCKB(450-(int)(painter->getCKBWigth(col)/2),10,col,row);
    painter->drawVKBmain(0,0);
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
