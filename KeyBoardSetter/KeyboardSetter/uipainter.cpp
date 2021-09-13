#include "hidcodetable.h"
#include "uipainter.h"

#include <QLabel>
#include <qpushbutton.h>


UIPainter::UIPainter(QWidget *ui, QObject *parent)
{
    this->my_ui = ui;
    this->Vkey_list = new QVector<QPushButton*>();
    this->CKBkey_list = new QVector<QPushButton*>();
    this->SW_list = new QVector<QPushButton*>();
}

//---------Paint Custom KeyBorad Functions---------------//
void UIPainter::drawCKBbase(int x,int y,int col,int row){
    QLabel *ql = new QLabel(this->my_ui);
    ql->setGeometry(x,y,(this->CKBKey_len+2*this->CKBKey_inter_margin)*col+2*this->CKBKey_ex_margin,(this->CKBKey_len+2*this->CKBKey_inter_margin)*row+2*this->CKBKey_ex_margin);
    ql->setStyleSheet("border-radius:15px;border:3px solid rgb(88, 96, 105);padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:20px;color:rgb(242, 242, 222);background-color:rgb(38, 46, 55);");
}

QPushButton* UIPainter::drawCKBkey(int x,int y,QString text){
    QPushButton *btn = new QPushButton(text,this->my_ui);
    btn->setGeometry(x,y,this->CKBKey_len,this->CKBKey_len);
    btn->clearMask();
    btn->setBackgroundRole(QPalette::Base);
    btn->setStyleSheet("QPushButton{background-color:rgb(48, 56, 65);border:2px solid rgb(88, 96, 105);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:20px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(88, 96, 105);}");
    return btn;
}

void UIPainter::drawCKB(int x,int y,int col,int row){
    drawCKBbase(x,y,col,row);
    QPushButton *btn_temp;
    int num = 1;
    for(int i=0;i<row;i++){
        for(int j =0;j<col;j++){
           btn_temp = drawCKBkey(x+j*(this->CKBKey_len+2*this->CKBKey_inter_margin)+this->CKBKey_ex_margin+this->CKBKey_inter_margin,y+i*(this->CKBKey_len+2*this->CKBKey_inter_margin)+this->CKBKey_ex_margin+this->CKBKey_inter_margin,QObject::tr("KEY")+QString::number(num));
           CKBkey_list->append(btn_temp);
           num++;
        }
    }
}

int UIPainter::getCKBWigth(int col)
{
    return (this->CKBKey_len+this->CKBKey_inter_margin*2)*col+this->CKBKey_ex_margin*2;
}

int UIPainter::getCKBHeight(int row)
{
    return (this->CKBKey_len+this->CKBKey_inter_margin*2)*row+this->CKBKey_ex_margin*2;
}

int UIPainter::getFullWindowHeight(int CKBrow)
{
    return getCKBHeight(CKBrow)+6*(this->VKey_len+this->Vkey_inter_margin)+4*this->UI_part_margin;
}

//--------------Paint Custom Mouse------------------------------//
void UIPainter::drawVMouse(int x,int y){
    int cur_x = x;
    int cur_y = y;
    QPushButton *lbtn = new QPushButton("",this->my_ui);
    QPushButton *mbtn = new QPushButton("",this->my_ui);
    QPushButton *rbtn = new QPushButton("",this->my_ui);
    this->mouse_body = new QLabel("",this->my_ui);
    //draw right mouse key
    lbtn->setGeometry(cur_x,cur_y,40,70);
    cur_x +=(40 + this->Vkey_inter_margin);
    lbtn->setStyleSheet("QPushButton{background-color:rgb(68, 76, 85);border:1px solid rgb(242, 242, 222);border-radius:7px;border-top-left-radius:30px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:10px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:rgb(168, 176, 185);}QPushButton:pressed{background-color:rgb(18, 26, 35);color:rgb(202, 202,182);}");
    //draw middle mouse key
    mbtn->setGeometry(cur_x,cur_y+15,15,40);
    cur_x +=(15 + this->Vkey_inter_margin);
    mbtn->setStyleSheet("QPushButton{background-color:rgb(68, 76, 85);border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:10px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:rgb(168, 176, 185);}QPushButton:pressed{background-color:rgb(18, 26, 35);color:rgb(202, 202,182);}");
    //draw left mouse key
    rbtn->setGeometry(cur_x,cur_y,40,70);
    cur_y +=(70 + this->Vkey_inter_margin);
    cur_x = x;
    rbtn->setStyleSheet("QPushButton{background-color:rgb(68, 76, 85);border:1px solid rgb(242, 242, 222);border-radius:7px;border-top-right-radius:30px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:10px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:rgb(168, 176, 185);}QPushButton:pressed{background-color:rgb(18, 26, 35);color:rgb(202, 202,182);}");
    //draw body
    mouse_body->setGeometry(cur_x,cur_y,95+2*this->Vkey_inter_margin,95+2*this->Vkey_inter_margin);
    mouse_body->setStyleSheet("background-color:rgb(68, 76, 85);border:1px solid rgb(242, 242, 222);border-radius:7px;border-bottom-right-radius:40px;border-bottom-left-radius:40px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:10px;color:rgb(242, 242, 222);");
    //append to maind list
    this->Vkey_list->append(lbtn);
    this->Vkey_list->append(mbtn);
    this->Vkey_list->append(rbtn);

}

void UIPainter::showVMouse()
{
    for(int i =103;i<106;i++){
        Vkey_list->data()[i]->show();
    }
    this->mouse_body->show();
}

void UIPainter::hideVMouse()
{
    for(int i =103;i<106;i++){
        Vkey_list->data()[i]->hide();
    }
    this->mouse_body->hide();
}



//--------------Paint Custom TabButton--------------------------//
QVector<QPushButton*> *UIPainter::getSW_list() const
{
    return SW_list;
}

void UIPainter::drawSwitch(int x, int y) const
{
    QPushButton *btn_kb = new QPushButton(tr("KEYBOARD"),this->my_ui);
    QPushButton *btn_mouse = new QPushButton(tr("MOUSE"),this->my_ui);
    QPushButton *btn_adv = new QPushButton(tr("ADVANCE"),this->my_ui);
    btn_kb->setStyleSheet("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(188, 181, 0,0), stop:1 rgba(205, 135, 0,0));border:1px solid rgb(242, 242, 222);border-top-left-radius:7px;border-bottom-left-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}");
    btn_mouse->setStyleSheet("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0,0), stop:1 rgba(0, 0, 0,0));border:1px solid rgb(242, 242, 222);padding:2px 4px;font: 5pt \"Microsoft YaHei UI\";font-size:12px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}");
    btn_adv->setStyleSheet("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0,0), stop:1 rgba(0, 0, 0,0));border:1px solid rgb(242, 242, 222);border-top-right-radius:7px;border-bottom-right-radius:7px;padding:2px 4px;font: 5pt \"Microsoft YaHei UI\";font-size:12px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}");
    btn_kb->setGeometry(x,y,80,20);
    btn_mouse->setGeometry(x+80-1,y,60,20);
    btn_adv->setGeometry(x+140-2,y,80,20);
    this->SW_list->append(btn_kb);
    this->SW_list->append(btn_mouse);
    this->SW_list->append(btn_adv);

}

void UIPainter::triggerSwitch(int btn_no)
{
    switch (btn_no){
        case 0:
            this->SW_list->data()[0]->setStyleSheet("QPushButton{background-color:rgb(138, 146, 155);border:1px solid rgb(242, 242, 222);border-top-left-radius:7px;border-bottom-left-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}");
            this->SW_list->data()[1]->setStyleSheet("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0,0), stop:1 rgba(0, 0, 0,0));border:1px solid rgb(242, 242, 222);padding:2px 4px;font: 5pt \"Microsoft YaHei UI\";font-size:12px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}");
            this->SW_list->data()[2]->setStyleSheet("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0,0), stop:1 rgba(0, 0, 0,0));border:1px solid rgb(242, 242, 222);border-top-right-radius:7px;border-bottom-right-radius:7px;padding:2px 4px;font: 5pt \"Microsoft YaHei UI\";font-size:12px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}");
            break;
        case 1:
            this->SW_list->data()[0]->setStyleSheet("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(188, 181, 0,0), stop:1 rgba(205, 135, 0,0));border:1px solid rgb(242, 242, 222);border-top-left-radius:7px;border-bottom-left-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}");
            this->SW_list->data()[1]->setStyleSheet("QPushButton{background-color:rgb(138, 146, 155);border:1px solid rgb(242, 242, 222);padding:2px 4px;font: 5pt \"Microsoft YaHei UI\";font-size:12px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}");
            this->SW_list->data()[2]->setStyleSheet("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0,0), stop:1 rgba(0, 0, 0,0));border:1px solid rgb(242, 242, 222);border-top-right-radius:7px;border-bottom-right-radius:7px;padding:2px 4px;font: 5pt \"Microsoft YaHei UI\";font-size:12px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}");
            break;
        case 2:
            this->SW_list->data()[0]->setStyleSheet("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(188, 181, 0,0), stop:1 rgba(205, 135, 0,0));border:1px solid rgb(242, 242, 222);border-top-left-radius:7px;border-bottom-left-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}");
            this->SW_list->data()[1]->setStyleSheet("QPushButton{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0,0), stop:1 rgba(0, 0, 0,0));border:1px solid rgb(242, 242, 222);padding:2px 4px;font: 5pt \"Microsoft YaHei UI\";font-size:12px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}");
            this->SW_list->data()[2]->setStyleSheet("QPushButton{background-color:rgb(138, 146, 155);border:1px solid rgb(242, 242, 222);border-top-right-radius:7px;border-bottom-right-radius:7px;padding:2px 4px;font: 5pt \"Microsoft YaHei UI\";font-size:12px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(15, 172, 252,255), stop:1 rgba(22, 190, 235,255));}QPushButton:pressed{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 160, 205,125), stop:1 rgba(0, 142, 222,125));color:rgb(202, 202,182);}");
            break;
        default:
            break;
    }
}

//-------------Paint Virtual KeyBoard Functions-------------------//

QPushButton* UIPainter::drawVKey(int x,int y,float block_x,float block_y,QString text){
    QPushButton *btn = new QPushButton(text,this->my_ui);
    btn->setGeometry(x,y,(this->VKey_len*block_x)+this->Vkey_inter_margin*(block_x-1.0),(this->VKey_len*block_y)+this->Vkey_inter_margin*(block_y-1.0));
    btn->setStyleSheet("QPushButton{background-color:rgb(68, 76, 85);border:1px solid rgb(242, 242, 222);border-radius:7px;padding:2px 4px;font: 9pt \"Microsoft YaHei UI\";font-size:10px;color:rgb(242, 242, 222);}QPushButton:hover{background-color:rgb(168, 176, 185);}QPushButton:pressed{background-color:rgb(18, 26, 35);color:rgb(202, 202,182);}");
    return btn;
}

void UIPainter::switchVinput(UIPainter::VinputEnable input)
{
    switch (input) {
        case VKEYBOARD:
            hideVMouse();
            showVKB();
            triggerSwitch(0);
            break;
        case VMOUSE:
            hideVKB();
            showVMouse();
            triggerSwitch(1);
            break;
        case VADVANCE:
            hideVKB();
            hideVMouse();
            triggerSwitch(2);
            break;
        default:
            break;
    }
}

QVector<QPushButton *> *UIPainter::getCKBkey_list() const
{
    return CKBkey_list;
}

QVector<QPushButton *> *UIPainter::getVkey_list() const
{
    return Vkey_list;
}

void UIPainter::drawVKBmain(int x,int y){
    HIDCodeTable *t = new HIDCodeTable();
    int i = 1;
    int cur_x = x;
    int cur_y = y;
    for(;i<=13;i++){
        if((i-2)%4==0)
            cur_x+= (int)((this->VKey_len+this->Vkey_inter_margin)*0.25);
        this->Vkey_list->append(drawVKey(cur_x,cur_y,1.1,1.0,t->getButtonNmae(i)));
        cur_x+= 1.1*this->VKey_len+this->Vkey_inter_margin;
    }
    cur_y+= this->VKey_len + this->Vkey_inter_margin;
    cur_x = x;
    for(;i<=27;i++){
        float block = 1.0;
        if(i==27)
            block = 2.0;
        this->Vkey_list->append(drawVKey(cur_x,cur_y,block,1.0,t->getButtonNmae(i)));
        cur_x+= this->VKey_len+this->Vkey_inter_margin;
    }
    cur_y+= this->VKey_len + this->Vkey_inter_margin;
    cur_x = x;
    for(;i<=41;i++){
        float block = 1.0;
        if(i==28 || i == 41)
            block = 1.5;
        if(i==29)
            cur_x += 0.5 * this->VKey_len;
        this->Vkey_list->append(drawVKey(cur_x,cur_y,block,1.0,t->getButtonNmae(i)));
        cur_x+= this->VKey_len+this->Vkey_inter_margin;
    }
    cur_y+= this->VKey_len + this->Vkey_inter_margin;
    cur_x = x;
    for(;i<=54;i++){
        float block = 1.0;
        if(i==42)
            block = 1.7;
        if(i==43)
            cur_x += 0.7 * this->VKey_len+this->CKBKey_inter_margin;
        if(i==54)
            block = 2.3;
        this->Vkey_list->append(drawVKey(cur_x,cur_y,block,1.0,t->getButtonNmae(i)));
        cur_x+= this->VKey_len+this->Vkey_inter_margin;
    }
    cur_y+= this->VKey_len + this->Vkey_inter_margin;
    cur_x = x;
    for(;i<=66;i++){
        float block = 1.0;
        if(i==55 || i == 66)
            block = 2.5;
        if(i==56)
            cur_x += 1.5 * this->VKey_len+this->CKBKey_inter_margin;
        this->Vkey_list->append(drawVKey(cur_x,cur_y,block,1.0,t->getButtonNmae(i)));
        cur_x+= this->VKey_len+this->Vkey_inter_margin;
    }
    cur_y+= this->VKey_len + this->Vkey_inter_margin;
    cur_x = x;
    for(;i<=73;i++){
        float block = 1.0;
        if(i!=70)
            block = 1.5;
        else
            block = 5.8;
        if(i>67 && i!=71)
            cur_x += 0.5 * this->VKey_len + this->CKBKey_inter_margin;
        if(i==71)
            cur_x += 5.0 * this->VKey_len + this->CKBKey_inter_margin;
        this->Vkey_list->append(drawVKey(cur_x,cur_y,block,1.0,t->getButtonNmae(i)));
        cur_x+= this->VKey_len+this->Vkey_inter_margin;
    }
    delete t;
}

void UIPainter::drawVKBfunc(int x,int y){
    HIDCodeTable *t = new HIDCodeTable();
    int i =74;
    int cur_x = x;
    int cur_y = y;
    for(int h=0;h<5;h++){
        cur_x = x;
        for(int w=0;w<3;w++){
            if(h==3){
                cur_y+= this->VKey_len + this->Vkey_inter_margin;
                cur_x += this->VKey_len+this->Vkey_inter_margin;
                this->Vkey_list->append(drawVKey(cur_x,cur_y,1.0,1.0,t->getButtonNmae(i)));
                i++;
                break;
            }
            else{
                this->Vkey_list->append(drawVKey(cur_x,cur_y,1.0,1.0,t->getButtonNmae(i)));
                i++;
                cur_x += this->VKey_len+this->Vkey_inter_margin;
            }
        }
        cur_y+= this->VKey_len + this->Vkey_inter_margin;
    }
    delete t;
}

void UIPainter::drawVKBkeypad(int x,int y){
    HIDCodeTable *t = new HIDCodeTable();
    int i =87;
    int cur_x = x;
    int cur_y = y;
    for(int h=0;h<5;h++){
        cur_x = x;
        for(int w=0;w<4 && i<=103;w++){
            if(w== 3 && (h==2 || h ==4))
                break;
            else if((h==1 || h ==3) && w==3)
                this->Vkey_list->append(drawVKey(cur_x,cur_y,1.0,2.0,t->getButtonNmae(i)));
            else if(h==4 && w==0 ){
                this->Vkey_list->append(drawVKey(cur_x,cur_y,2.0,1.0,t->getButtonNmae(i)));
                cur_x += this->VKey_len+this->Vkey_inter_margin;
            }
            else
                this->Vkey_list->append(drawVKey(cur_x,cur_y,1.0,1.0,t->getButtonNmae(i)));
            i++;
            cur_x += this->VKey_len+this->Vkey_inter_margin;
        }
        cur_y+= this->VKey_len + this->Vkey_inter_margin;
    }
    delete t;
}

void UIPainter::drawVKBfull(int x,int y){
    int VKBpart_margin = 0.3*this->VKey_len;
    drawVKBmain(x,y);
    drawVKBfunc(x+15*(this->VKey_len+this->Vkey_inter_margin)+VKBpart_margin,y);
    drawVKBkeypad(x+18*(this->VKey_len+this->Vkey_inter_margin)+2*VKBpart_margin,y+this->VKey_len+this->Vkey_inter_margin);
}

void UIPainter::hideVKB()
{
    for(int i = 0;i<103;i++)
        this->Vkey_list->data()[i]->hide();
}
void UIPainter::showVKB(){
    for(int i = 0;i<103;i++)
        this->Vkey_list->data()[i]->show();
}


//--------------Paint Full UI-----------------------------------//


//--------------Paint Function button UI -----------------------//





//------------Getter and Setter -----------------------------------//
void UIPainter::setCKBKey_len(int value)
{
    CKBKey_len = value;
}
void UIPainter::setCKBKey_inter_margin(int value)
{
    CKBKey_inter_margin = value;
}
void UIPainter::setCKBKey_ex_margin(int value)
{
    CKBKey_ex_margin = value;
}
void UIPainter::setVKey_len(int value)
{
    VKey_len = value;
}
void UIPainter::setVkey_inter_margin(int value)
{
    Vkey_inter_margin = value;
}

int UIPainter::getUI_part_margin() const
{
    return UI_part_margin;
}

void UIPainter::setUI_part_margin(int value)
{
    UI_part_margin = value;
}
