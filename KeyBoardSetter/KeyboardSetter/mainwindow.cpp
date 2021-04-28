#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

//public ui
QLabel *softkey_out;


//puclic key board string
QString key_string[]={
    //normal keys
    "Escape","F1","F2","F3","F4","F5","F6","F7","F8","F9","F10","F11","F12",
    "~","1","2","3","4","5","6","7","8","9","0","-","+","Backspace",
    "Tab","Q","W","E","R","T","Y","U","I","O","P","[","]","\\",
    "Caps Lock","A","S","D","F","G","H","J","K","L",";","\'","Enter",
    "Left Shift","Z","X","C","V","B","N","M","<",">","?","Right Shift",
    "Left Ctrl","Left Win","Left Alt","Space","Right Alt","Right Win","Right Ctrl",
    //right area keys
    "Print Screen","Delete","Insert",
    "Arrow UP","Arrow Left","Arrow Down","Arrow Right"

};
uchar key_hex[]={
    0x29,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,0x40,0x41,0x42,0x43,0x44,0x45,
    0x35,0x1e,0x1f,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x2d,0x2e,0x2a,
    0x2b,0x14,0x1a,0x08,0x15,0x17,0x1c,0x18,0x0c,0x12,0x13,0x2f,0x30,0x31,
    0x82,0x04,0x16,0x07,0x09,0x0a,0x0b,0x0d,0x0e,0x0f,0x33,0x34,0x58,
    /*Lshift*/0x02,0x1d,0x1b,0x06,0x19,0x05,0x11,0x10,0x36,0x37,0x38,/*Rshift*/0x20,
    /*Lctrl*/ 0x01,0x08,0x04,0x2c,0x40,0x80,0x10,
    //right area keys
    0x46,0x4c,0x49,
    0x52,0x50,0x51,0x45
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    softkey_out = ui->tvkey_out;
    //button init
    QToolButton *keyboard_list[]={
        //normal keys
        ui->btn_esc,ui->btn_f1,ui->btn_f2,ui->btn_f3,ui->btn_f4,ui->btn_f5,ui->btn_f6,ui->btn_f7,ui->btn_f8,ui->btn_f9,ui->btn_f10,ui->btn_f11,ui->btn_f12,
        ui->btn_wave,ui->btn_1,ui->btn_2,ui->btn_3,ui->btn_4,ui->btn_5,ui->btn_6,ui->btn_7,ui->btn_8,ui->btn_9,ui->btn_0,ui->btn_minus,ui->btn_add,ui->btn_backspace,
        ui->btn_tab,ui->btn_q,ui->btn_w,ui->btn_e,ui->btn_r,ui->btn_t,ui->btn_y,ui->btn_u,ui->btn_i,ui->btn_o,ui->btn_p,ui->btn_leftbracket,ui->btn_rightbracket,ui->btn_splash,
        ui->btn_caps,ui->btn_a,ui->btn_s,ui->btn_d,ui->btn_f,ui->btn_g,ui->btn_h,ui->btn_j,ui->btn_k,ui->btn_l,ui->btn_split,ui->btn_quote,ui->btn_enter,
        ui->btn_lshift,ui->btn_z,ui->btn_x,ui->btn_c,ui->btn_v,ui->btn_b,ui->btn_n,ui->btn_m,ui->btn_lessthan,ui->btn_greaterthan,ui->btn_quest,ui->btn_rshift,
        ui->btn_lctrl,ui->btn_lwin,ui->btn_lalt,ui->btn_space,ui->btn_ralt,ui->btn_rwin,ui->btn_rctrl,
        //right area keys
        ui->btn_ptsr,ui->btn_del,ui->btn_ins,
        ui->btn_up,ui->btn_left,ui->btn_down,ui->btn_right
    };

    //connect soft-keyboard toolbuttons
    int total = (int)(sizeof(keyboard_list)/sizeof(QToolButton*));
    qDebug() << "Total key number is :" + QString::number(total)<<endl;
    for(int i = 0;i<total;i++){
        connect(keyboard_list[i],&QToolButton::clicked,this,[=]{
            softKeyPressed(i);
        });
    }


    //connect menu bar action
    connect(ui->actionExit,&QAction::triggered,this,&MainWindow::close);
    connect(ui->btn_setcancel,&QPushButton::clicked,ui->dockKeyboard,[=]{
        //ui->dockKeyboard->move(ui->dockKeyboard->pos().x(),ui->dockKeyboard->pos().y()+100);
    });
}
//soft key press function
void MainWindow::softKeyPressed(int i){
    softkey_out->setText(key_string[i]+"  i:"+QString::number(i));
}
MainWindow::~MainWindow()
{
    delete ui;
}

