#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "customkeyboard.h"
#include "hidcodetable.h"
#include "keyvalue.h"
#include "hidapi.h"
#include <QDebug>
#include <QTimer>
#include <QStandardItem>
#include <QMessageBox>

#define DEBUG 1
#define TYPENUM 3

//global vars
HIDCodeTable table;
//custom key board class
CustomKeyboard *ckb[TYPENUM];
QVector<QStandardItemModel*> models;

//current pressed key
QVector<int> cur_key_sp;
QVector<int> cur_key_normal;

//current select keyboard
int cur_keyboard_no = 0;//-1 repersent none
int cur_edit_key_no = -1;

//timer for long press
QTimer *press_timer = new QTimer;
//delay 500ms and jump to funtion setKey()

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    //virtual key
    //TEST keyboard page
    QPushButton *virtual_test_keys[]{
        ui->btn_testkey1,ui->btn_testkey2,ui->btn_testkey3,ui->btn_testkey4,ui->btn_testkey5,
        ui->btn_testkey6,ui->btn_testkey7,ui->btn_testkey8,ui->btn_testkey9,ui->btn_testkey10
    };
    //Dual keyboard page
    QPushButton *virtual_dual_keys[]{
        ui->btn_dualkey1,ui->btn_dualkey2
    };
    //Qua keyboard page
    QPushButton *virtual_qua_keys[]{
        ui->btn_quakey1,ui->btn_quakey2,
        ui->btn_quakey3,ui->btn_quakey4
    };

    ckb[0] = new CustomKeyboard("Test",10,0x2019,0x5131,100,20,virtual_test_keys);//test keyboard
    ckb[1] = new CustomKeyboard("DualKey",2,0x2019,0x5131,100,20,virtual_dual_keys);//double-key keyboard
    ckb[2] = new CustomKeyboard("QuadraKey",4,0x2019,0x5131,100,20,virtual_qua_keys);//quadra-key keyboard

    int total = (int)(sizeof(keyboard_list)/sizeof(QToolButton*));
    #ifdef DEBUG
    qDebug() << "Total key number is :" + QString::number(total)<<endl;
    #endif
    //CONNECT FUNCTIONS
    //connect soft-keyboard toolbuttons
    for(int i = 1;i<total+1;i++){
        connect(keyboard_list[i-1],&QToolButton::clicked,this,[=]{
            softKeyPressed(i);
        });
    }
    for(int i =0;i<TYPENUM;i++){
        for(int j =0;j<ckb[i]->getKeynum();j++){
            connect(ckb[i]->getButtonByID(j),&QPushButton::clicked,this,[=]{
                setKey(j);
            });
        }
    }
    //connect tag-widget
    connect(ui->tabWidget,&QTabWidget::currentChanged,this,[=]{
        switchKeyboard(ui->tabWidget->currentIndex());
        ui->dockKeyboard->hide();
    });
    //connect menu bar action
    connect(ui->actionExit,&QAction::triggered,this,&MainWindow::close);
    connect(ui->btn_setcancel,&QPushButton::clicked,ui->dockKeyboard,[=]{
        cur_key_sp.clear();
        cur_key_normal.clear();
        updateUI();
        //hide key board
        ui->dockKeyboard->hide();
    });

    //commit key setting
    connect(ui->btn_setcommit,&QPushButton::clicked,this,[=]{
       commitKeySetting();
    });

    //download button
    connect(ui->btn_download,&QPushButton::clicked,this,[=]{
        downloadToDevice(cur_keyboard_no);
    });

    //init UI
    initTreeView();
    ui->treeView->setModel(models[0]);
    ui->dockKeyboard->hide();


}

//----------SLOTS
void MainWindow::setKeyPress(int key_no){
    press_timer->start(500);
}
void MainWindow::setKeyRelease(){
    press_timer->stop();
}
void MainWindow::switchKeyboard(int keyboard_no){
    cur_keyboard_no = keyboard_no;
    updateUI();
}
void MainWindow::setKey(int key_no){
    cur_edit_key_no = key_no;
    ui->dockKeyboard->setWindowTitle("Current Keyboard:"+ckb[cur_keyboard_no]->getName()+"   Current Seletion:KEY"+QString::number(key_no+1));
    ui->dockKeyboard->show();
};

void MainWindow::commitKeySetting(){
    if(cur_key_sp.size()>0||cur_key_normal.size()>0){
        KeyValue *vkp = table.convertVector2KeyValue(cur_key_normal[0],cur_key_sp);
        ckb[cur_keyboard_no]->setKey(cur_edit_key_no,vkp);

        QModelIndex temp_index = models[cur_keyboard_no]->index(cur_edit_key_no,0);
        models[cur_keyboard_no]->itemFromIndex(temp_index)->setChild(0,0,new QStandardItem("1"));
        models[cur_keyboard_no]->itemFromIndex(temp_index)->setChild(0,1,new QStandardItem(table.convertKeyValue2QString(vkp)));


        //clear current buffer
        cur_key_normal.clear();
        cur_key_sp.clear();
        cur_edit_key_no = -1;
        ui->dockKeyboard->hide();
        updateUI();
    }
}

void MainWindow::initTreeView(){
    for(int x =0;x<TYPENUM;x++){
        QStandardItemModel* model = new QStandardItemModel(ui->treeView);
        //set header
        model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("NAME") << QStringLiteral("DESCRIPTION"));
        CustomKeyboard *ckd_temp = ckb[x];
        for(int i = 0;i<ckd_temp->getKeynum();i++){
            QList<QStandardItem*> ikeys;
            QStandardItem* ikey = new QStandardItem(ckd_temp->getCustomKeyByID(i)->getName());
            QStandardItem* detail;
            if(ckd_temp->getCustomKeyByID(i)->isMarco())
                detail =new QStandardItem(QStringLiteral("Marco"));
            else
                detail =new QStandardItem(QStringLiteral("Normal"));
            ikeys.append(ikey);
            ikeys.append(detail);
            model->appendRow(ikeys);
            QVector<KeyValue*> kvlist_temp = ckd_temp->getCustomKeyByID(i)->getKeyValueList();
            for(int j=0;j<kvlist_temp.size();j++){
                QList<QStandardItem*> ikvs;
                QStandardItem* ikv = new QStandardItem(QString::number(j+1));
                QStandardItem* key_detail = new QStandardItem(table.convertKeyValue2QString(kvlist_temp[j]));
                ikvs.append(ikv);
                ikvs.append(key_detail);
                ikey->appendRow(ikvs);
            }
        }
        models.append(model);
    }
    //set treeview uneditable
    ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

//soft key press function
void MainWindow::softKeyPressed(int i){
    if(table.isSPkey(i)){
        if(cur_key_sp.indexOf(i)>=0){
            //the key is pressed
            cur_key_sp.remove(cur_key_sp.indexOf(i));
        }
        else{
            //key is not pressed
            cur_key_sp.append(i);
        }
    }
    else{
        if(cur_key_normal.indexOf(i)>=0)
            cur_key_normal.clear();
        else{
            cur_key_normal.clear();
            cur_key_normal.append(i);
        }
    }

   // softkey_out->setText(key_string[i]+"  i:"+QString::number(i));
    updateUI();
}
// update ui
void MainWindow::updateUI(){
    //update soft keyboard label
    QString temp = "";
    if(!cur_key_sp.isEmpty()){
        temp = table.getKeyString(cur_key_sp[0]);
        for(int i = 1;i<cur_key_sp.size();i++){
            temp += " + " +  table.getKeyString(cur_key_sp[i]);
        }
    }
    if(!cur_key_normal.isEmpty()){
        int i = 0;
        if(temp == ""){
            temp = table.getKeyString(cur_key_normal[0]);
            i++;
        }
        for(;i<cur_key_normal.size();i++){
            temp += " + " +  table.getKeyString(cur_key_normal[i]);
        }
    }
    ui->tvkey_out->setText(temp);
    ui->treeView->setModel(models[cur_keyboard_no]);
}

bool MainWindow::downloadToDevice(int keyboard_no){
    QMessageBox msg_info(this);
    msg_info.setWindowTitle("Notice");
    msg_info.setText("Are you sure to download config to your device:" + ckb[keyboard_no]->getName()+"?");
    msg_info.setIcon(QMessageBox::Question);
    msg_info.setStandardButtons(QMessageBox::Ok | QMessageBox:: Cancel);
    if(msg_info.exec() == QMessageBox::Ok){
        QMessageBox msg_result(this);
        if(ckb[keyboard_no]->download()){
            msg_result.setWindowTitle("Notice");
            msg_result.setText("Download finished!");
            msg_result.setIcon(QMessageBox::Information);
            msg_result.setStandardButtons(QMessageBox::Ok);
        }
        else{
            msg_result.setWindowTitle("Error");
            msg_result.setText("Download Error :" + ckb[keyboard_no]->getLastError());
            msg_result.setIcon(QMessageBox::Critical);
            msg_result.setStandardButtons(QMessageBox::Ok);
        }
        msg_result.exec();
    }
};


MainWindow::~MainWindow()
{
    delete ui;
}




