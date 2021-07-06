#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "customkeyboard.h"
#include "hidcodetable.h"
#include "keyvalue.h"
#include "hidapi.h"
#include "configsaver.h"
#include "userconfig.h"
#include <QDebug>
#include <QTimer>
#include <QStandardItem>
#include <QMessageBox>
#include <qjsondocument.h>
#include <QFileDialog>
#include <qtranslator.h>

#define TYPENUM 3
#define KEYNUM 10

//global vars
HIDCodeTable table;
QToolButton **keyboard_list_g;
//custom key board class
CustomKeyboard *ckb[TYPENUM];

QVector<QStandardItemModel*> models;

//current pressed key
QVector<int> cur_key_sp;
QVector<int> cur_key_normal;
int cur_mouse =0;
int cur_media =0;
int cur_delay =0;

//current select keyboard
int cur_keyboard_no = 0;//-1 repersent none
int cur_edit_key_no = -1;

//timer for long press
QTimer *press_timer = new QTimer;
//delay 500ms and jump to funtion setKey()

//Translator
QTranslator *translator;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //inti translator
    translator = new QTranslator();
    //load from config
    ConfigSaver cs;
    QString filename =  QCoreApplication::applicationDirPath() + "//usercondif.ini";
    QJsonObject *jsonobj = new QJsonObject();
    if(!cs.readConfig(filename,jsonobj))
        qDebug() << "Can not read userconfig.ini";
    UserConfig *uc = UserConfig::fromJson(*jsonobj);
    if(uc->getLanguage()=="english"){
        changeLanguage("en");
    }else{
        changeLanguage("cn");
    }

    //button init
    static QToolButton *keyboard_list[]={
        //normal keys
        ui->btn_esc,ui->btn_f1,ui->btn_f2,ui->btn_f3,ui->btn_f4,ui->btn_f5,ui->btn_f6,ui->btn_f7,ui->btn_f8,ui->btn_f9,ui->btn_f10,ui->btn_f11,ui->btn_f12,
        ui->btn_wave,ui->btn_1,ui->btn_2,ui->btn_3,ui->btn_4,ui->btn_5,ui->btn_6,ui->btn_7,ui->btn_8,ui->btn_9,ui->btn_0,ui->btn_minus,ui->btn_add,ui->btn_backspace,
        ui->btn_tab,ui->btn_q,ui->btn_w,ui->btn_e,ui->btn_r,ui->btn_t,ui->btn_y,ui->btn_u,ui->btn_i,ui->btn_o,ui->btn_p,ui->btn_leftbracket,ui->btn_rightbracket,ui->btn_splash,
        ui->btn_caps,ui->btn_a,ui->btn_s,ui->btn_d,ui->btn_f,ui->btn_g,ui->btn_h,ui->btn_j,ui->btn_k,ui->btn_l,ui->btn_split,ui->btn_quote,ui->btn_enter,
        ui->btn_lshift,ui->btn_z,ui->btn_x,ui->btn_c,ui->btn_v,ui->btn_b,ui->btn_n,ui->btn_m,ui->btn_lessthan,ui->btn_greaterthan,ui->btn_quest,ui->btn_rshift,
        ui->btn_lctrl,ui->btn_lwin,ui->btn_lalt,ui->btn_space,ui->btn_ralt,ui->btn_rwin,ui->btn_rctrl,
        //right area keys
        ui->btn_ptsr,ui->btn_scrolllock,ui->btn_puase,
        ui->btn_insert,ui->btn_home,ui->btn_pageup,
        ui->btn_delete,ui->btn_end,ui->btn_pagedown,
        ui->btn_up,ui->btn_left,ui->btn_down,ui->btn_right,
        //key pad
        ui->btn_num,ui->btn_sslash,ui->btn_star,ui->btn_sminus,
        ui->btn_s7,ui->btn_s8,ui->btn_s9,ui->btn_splus,
        ui->btn_s4,ui->btn_s5,ui->btn_s6,
        ui->btn_s1,ui->btn_s2,ui->btn_s3,ui->btn_senter,
        ui->btn_s0,ui->btn_sdot,
        //mouse
        ui->btn_mouseleft,ui->btn_mousemiddle,ui->btn_mouseright,
        //media
        ui->btn_mmvd,ui->btn_mmvp,ui->btn_mmpp,ui->btn_mmls,ui->btn_mmns,ui->btn_mmmute,
        //f13-f24
        ui->btn_f13,ui->btn_f14,ui->btn_f15,ui->btn_f16,ui->btn_f17,ui->btn_f18,
        ui->btn_f19,ui->btn_f20,ui->btn_f21,ui->btn_f22,ui->btn_f23,ui->btn_f24
    };
    keyboard_list_g = keyboard_list;
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

    ckb[0] = new CustomKeyboard("Test",10,0x2019,0x5131,virtual_test_keys);//test keyboard
    ckb[1] = new CustomKeyboard("DualKey",2,0x2019,0x5131,virtual_dual_keys);//double-key keyboard
    ckb[2] = new CustomKeyboard("QuadraKey",4,0x2019,0x5131,virtual_qua_keys);//quadra-key keyboard

    //version justify
    int version = 0;
    while(true){
        version = ckb[0]->getVersion();
        if(version<0){
            QMessageBox msg_info(this);
            msg_info.setWindowTitle(tr("Notice"));
            msg_info.setText(tr("Device not found,please connect then press ok."));
            msg_info.setIcon(QMessageBox::Information);
            msg_info.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
            if(msg_info.exec()==QMessageBox::Cancel){
                break;
            }
        }else
            break;
    }

    if(version == 0){
        logUpdate("device firmware is old,reset limits.");
        ckb[0]->setMacroConfig(40,4,10,10);
    }
    else if(version == 1){
        logUpdate("device firmware is new");
    }else{
        logUpdate("device not found.");
    }

    int total = (int)(sizeof(keyboard_list)/sizeof(QToolButton*));
    qDebug() << "Total key number is :" + QString::number(total)<<endl;
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
    //connect log event slot
    connect(ckb[0],&CustomKeyboard::logToMain,this,&MainWindow::logUpdate);
    //connect menu bar action
    connect(ui->actionExit,&QAction::triggered,this,&MainWindow::close);
    connect(ui->actionSave,&QAction::triggered,this,[=]{
        saveConfigToFile();
    });
    connect(ui->actionLoad,&QAction::triggered,this,[=]{
        loadConfigFromFile();
    });
    connect(ui->actionTest_Device,&QAction::triggered,this,[=]{
        ckb[0]->testHardware();
    });
    connect(ui->actionEnglish,&QAction::triggered,this,[=]{
        //set UI to english
        ui->actionChinese->setChecked(false);
        changeLanguage("en");
    });
    connect(ui->actionChinese,&QAction::triggered,this,[=]{
        //set UI to english
        ui->actionEnglish->setChecked(false);
        changeLanguage("cn");
    });
    connect(ui->actionGetVersion,&QAction::triggered,this,[=]{
        ckb[0]->getVersion();
    });
    //


    //connect button
    connect(ui->btn_setcancel,&QPushButton::clicked,ui->dockKeyboard,[=]{
        //clear current stat
        cur_key_sp.clear();
        cur_key_normal.clear();
        cur_mouse =0;
        cur_media =0;
        cur_delay =0;
        ui->btn_lshift->setStyleSheet("");
        ui->btn_lctrl->setStyleSheet("");
        ui->btn_lalt->setStyleSheet("");
        ui->btn_lwin->setStyleSheet("");
        ui->btn_rshift->setStyleSheet("");
        ui->btn_rctrl->setStyleSheet("");
        ui->btn_ralt->setStyleSheet("");
        ui->btn_rwin->setStyleSheet("");
        updateUI();
        //hide key board
        ui->dockKeyboard->hide();
        this->resize(1000,370);
    });

    //commit key setting
    connect(ui->btn_load,&QPushButton::clicked,this,[=]{
       //commitKeySetting();
       loadConfigFromFile();
    });

    //download button
    connect(ui->btn_download,&QPushButton::clicked,this,[=]{
        downloadToDevice(cur_keyboard_no);
    });
    //set add and delete button
    connect(ui->btn_setadd,&QPushButton::clicked,this,[=]{
        addKeyValue();
    });
    connect(ui->btn_setdelete,&QPushButton::clicked,this,[=]{
        deleteKeyValue();
    });
    //set delay increasement and decreasement
    connect(ui->btn_delayplus,&QPushButton::clicked,this,[=]{
        delayindecrease();
    });
    connect(ui->btn_delayminus,&QPushButton::clicked,this,[=]{
        delayindecrease(false);
    });
    //set set-delay button
    connect(ui->btn_setdelay,&QPushButton::clicked,this,[=]{
        setDelay();
    });
    //set save button
    connect(ui->btn_save,&QPushButton::clicked,this,[=]{
        saveConfigToFile();
    });

    //init UI
    //init et_delay
    QRegExp rx("[12]?\\d\\.[0-9]");
    QRegExpValidator *pRevalidotor = new QRegExpValidator(rx,this);
    ui->et_delay->setValidator(pRevalidotor);

    initTreeView();
    ui->treeView->setModel(models[0]);
    ui->dockKeyboard->hide();
    ui->btn_setadd->hide();

    //init window
    this->resize(1000,370);

    //set tips
    ui->btn_setadd->setToolTip(tr("Click this to add single Crtl,Alt,Shift to key value"));

    //release
    delete jsonobj;
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
    cur_key_sp.clear();
    cur_key_normal.clear();
    cur_mouse =0;
    cur_media =0;
    cur_delay =0;
    cur_edit_key_no = 0;
    updateUI();
}
/** ***********************************************
*
* Set UI language in real time
* @author   oscar
* @date     2021/06/17
* @param   QString language: "cn" for chinese , "en" for english
*
***************************************************/
void MainWindow::changeLanguage(QString language)
{
    QString flag = "english";
    if(language=="cn"){
        QString path = QCoreApplication::applicationDirPath() + "//trans_zh_CN.qm";
        translator->load(path);
        if(qApp->installTranslator(translator)){
            ui->retranslateUi(this);   //refresh ui
            ui->actionChinese->setChecked(true);
            ui->actionEnglish->setChecked(false);
            flag = "chinese";
        }
        else{
            qDebug() << "Can not load UI language.";
            logUpdate("Can not load UI language.");
        }
    }else if(language=="en"){
        translator->load("");
        qApp->installTranslator(translator);
        ui->retranslateUi(this);    //refresh ui
        ui->actionChinese->setChecked(false);
        ui->actionEnglish->setChecked(true);
        flag = "english";
        qDebug() << "Using english as UI language.";
        logUpdate("Using english as UI language.");
    }

    //save user language information to file
    UserConfig *userconfig = new UserConfig(flag);
    ConfigSaver cs;
    QString filename =  QCoreApplication::applicationDirPath() + "//usercondif.ini";
    if(!cs.saveConfig(filename,userconfig->toJsonObj()))
        qDebug()  << cs.getLastError();
    delete userconfig;
}

void MainWindow::logUpdate(QString text)
{
    ui->tv_log->append(text);
}

void MainWindow::findDevice(CustomKeyboard *my_ckb)
{
    hid_device *my_device = hid_open(my_ckb->getVid(),my_ckb->getPid(),nullptr);
    if(my_device!=nullptr){

    }
}

void MainWindow::setKey(int key_no){
    cur_edit_key_no = key_no;
    ui->dockKeyboard->setWindowTitle(tr("Current Keyboard")+":"+ckb[cur_keyboard_no]->getName()+"   "+tr("Current Seletion")+":KEY"+QString::number(key_no+1));
    this->resize(1000,650);
    ui->dockKeyboard->show();
    updateUI();
};

//Key listener
QT_DEPRECATED
void MainWindow::commitKeySetting(){
    if(cur_key_sp.size()>0||cur_key_normal.size()>0){
        int temp = 0;
        if(cur_key_normal.size() > 0)
            temp = cur_key_normal[0];
        KeyValue *vkp = table.convertVector2KeyValue(temp,0,0,cur_key_sp);
        ckb[cur_keyboard_no]->setKey(cur_edit_key_no,vkp);

        QModelIndex temp_index = models[cur_keyboard_no]->index(cur_edit_key_no,0);
        models[cur_keyboard_no]->itemFromIndex(temp_index)->child(0,1)->setText(table.convertKeyValue2QString(vkp));

        //clear current buffer
        cur_key_normal.clear();
        cur_key_sp.clear();
        cur_edit_key_no = -1;
        ui->dockKeyboard->hide();
        updateUI();
    }
}

void MainWindow::setDelay(){
    QString temp = ui->et_delay->text();
    float delay = temp.toFloat();
    int delay_int = (int)(delay * 10);
    cur_delay = (uchar) delay_int;
    updateUI();
}

bool MainWindow::saveConfigToFile()
{
    QMessageBox msg_info(this);
    msg_info.setWindowTitle(tr("Notice"));
    msg_info.setText(tr("Save config to file?"));
    msg_info.setIcon(QMessageBox::Question);
    msg_info.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    if(msg_info.exec()==QMessageBox::Ok){
        //press ok
        QString filePath = QFileDialog::getSaveFileName(this, tr("Save File"),".//untitled.zdd",tr("zddConfig (*.zdd)"));
        qDebug() << filePath << "is selected";
        if(filePath != ""){
            ConfigSaver* saver =new ConfigSaver();
            if(!saver->saveConfig(filePath,ckb[cur_keyboard_no]->toJsonObj())){
                //can not save
                QMessageBox msg_info(this);
                msg_info.setWindowTitle(tr("Error"));
                msg_info.setText(tr("Can not save ")+filePath+" "+saver->getLastError());
                msg_info.setIcon(QMessageBox::Critical);
                msg_info.setStandardButtons(QMessageBox::Ok);
                msg_info.exec();
            }else{
                QMessageBox msg_info(this);
                msg_info.setWindowTitle(tr("Notice"));
                msg_info.setText(tr("Saved Successfully!"));
                msg_info.setIcon(QMessageBox::Information);
                msg_info.setStandardButtons(QMessageBox::Ok);
                msg_info.exec();
            }
            delete saver;

        }
    }

}

CustomKeyboard *MainWindow::loadConfigFromFile()
{
    QMessageBox msg_info(this);
    msg_info.setWindowTitle(tr("Notice"));
    msg_info.setText(tr("Load config?"));
    msg_info.setIcon(QMessageBox::Question);
    msg_info.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    if(msg_info.exec()==QMessageBox::Ok){
        //press ok
        QString filePath = QFileDialog::getOpenFileName(this,tr("Open file"),"./",tr("zddConfig (*.zdd)"));
        qDebug() << filePath << "is selected";
        if(filePath != ""){
            ConfigSaver* saver =new ConfigSaver();
            QJsonObject ckbjsonobj;
            if(!saver->readConfig(filePath,&ckbjsonobj)){
                //can not save
                QMessageBox msg_info(this);
                msg_info.setWindowTitle(tr("Error"));
                msg_info.setText(tr("Can not load file ")+filePath+" "+saver->getLastError());
                msg_info.setIcon(QMessageBox::Critical);
                msg_info.setStandardButtons(QMessageBox::Ok);
                msg_info.exec();
            }else{
                //virtual key
                //TEST keyboard page
                QPushButton *virtual_test_keys[]{
                    ui->btn_testkey1,ui->btn_testkey2,ui->btn_testkey3,ui->btn_testkey4,ui->btn_testkey5,
                    ui->btn_testkey6,ui->btn_testkey7,ui->btn_testkey8,ui->btn_testkey9,ui->btn_testkey10
                };

                ckb[0] = CustomKeyboard::fromJson(ckbjsonobj,virtual_test_keys);
                updateUI();
                QMessageBox msg_info(this);
                msg_info.setWindowTitle(tr("Notice"));
                msg_info.setText(tr("Loaded Successfully!"));
                msg_info.setIcon(QMessageBox::Information);
                msg_info.setStandardButtons(QMessageBox::Ok);
                msg_info.exec();
            }
            delete saver;
        }
    }
}
void MainWindow::delayindecrease(bool is_add){
    QString temp = ui->et_delay->text();
    float delay = temp.toFloat();
    if(is_add){
        //increase delay
        if(delay < 25.5f)
            delay += 0.1f;
        else{
            delay = 25.5f;
        }
    }
    else{
        //decrease delay
        if(delay > 0.1f)
            delay -= 0.1f;
        else
            delay = 0.0f;
    }
    ui->et_delay->setText(QString::number(delay));
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
            if(ckd_temp->getCustomKeyByID(i)->isMacro())
                detail =new QStandardItem(QStringLiteral("Macro"));
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
    ui->btn_setadd->show();
    if(table.isSPkey(i)){
        //clear single key except normal key
        cur_media = 0;
        cur_mouse = 0;
        //special key pressed
        if(cur_key_sp.indexOf(i)>=0){
            //the key is pressed
            cur_key_sp.remove(cur_key_sp.indexOf(i));
            keyboard_list_g[i-1]->setStyleSheet("");
        }
        else{
            //key is not pressed
            cur_key_sp.append(i);
            //set keys color
            keyboard_list_g[i-1]->setStyleSheet("background-color: rgb(255, 100, 100);");
        }
    }
    else if(table.isMouseKey(i)){
        //clear other single key
        cur_media = 0;
        //clear noraml
        if(cur_key_normal.size()>0){
            cur_key_normal[0]=0;
            cur_key_sp.clear();
        }
        if(cur_mouse==i)
            cur_mouse = 0;
        else{
            cur_mouse = i;
            addKeyValue();
        }
    }
    else if(table.isMediaKey(i)){
        //clear other single key
       cur_mouse = 0;
       if(cur_key_normal.size()>0){
           cur_key_normal[0]=0;
           cur_key_sp.clear();
       }
       if(cur_media==i)
           cur_media = 0;
       else{
           cur_media = i;
           addKeyValue();
       }
    }
    else
    {
        //clear other single key
        cur_media = 0;
        cur_mouse = 0;
        //normal key pressed
        if(cur_key_normal.indexOf(i)>=0)
            cur_key_normal.clear();
        else{
            cur_key_normal.clear();
            cur_key_normal.append(i);
            addKeyValue();
        }
    }
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
    if(cur_delay!=0){
        temp = "Delay"+ ui->et_delay->text() +"s"+temp;
    }
    // these keys is single
    if(cur_media!=0){
        temp = table.getKeyString(cur_media);
    }
    if(cur_mouse!=0){
        temp = table.getKeyString(cur_mouse);
    }

    //set selector color
    if(cur_edit_key_no != -1){
        //show cur key
        QString str_temp ="";
        QVector<KeyValue*> kvs = ckb[cur_keyboard_no]->getCustomKeyByID(cur_edit_key_no)->getKeyValueList();
        if(!kvs.isEmpty()){
            str_temp = "(" + table.convertKeyValue2QString(kvs[0])+")";
            for(int i =1;i<kvs.size();i++){
                str_temp += " + ("+table.convertKeyValue2QString(kvs[i])+")";
            }
        }
        //set text
        if(temp != ""){
            if(str_temp == "(None)")
                ui->tv_keyvalue->setText("("+ temp + " + )");
            else
                ui->tv_keyvalue->setText(str_temp + " + ("+ temp + " + )");
        }
        else
            ui->tv_keyvalue->setText(str_temp);
        ckb[cur_keyboard_no]->getButtonByID(cur_edit_key_no)->setStyleSheet("background-color: rgb(255, 100, 100);"); //red for selected
    }

    //set color color
    for(int i=0;i<ckb[cur_keyboard_no]->getKeynum();i++){
        if(i == cur_edit_key_no)
            continue;
        QPushButton *pbtn = ckb[cur_keyboard_no]->getButtonByID(i);
        if(ckb[cur_keyboard_no]->getCustomKeyByID(i)->isMacro())
            pbtn->setStyleSheet("background-color: rgb(255, 100, 255);"); //purple for macro
        else if(ckb[cur_keyboard_no]->getCustomKeyByID(i)->isMedia())
            pbtn->setStyleSheet("background-color: rgb(255, 200, 100);"); //yellow for media
        else if(ckb[cur_keyboard_no]->getCustomKeyByID(i)->isMouse())
            pbtn->setStyleSheet("background-color: rgb(100, 255, 100);"); //green for mouse
        else{
            if(ckb[cur_keyboard_no]->getCustomKeyByID(i)->getKeyValueCount()==1
                    && (ckb[cur_keyboard_no]->getCustomKeyByID(i)->getKeyValueList()[0]->getNormalKeyIndex()!=0
                        ||ckb[cur_keyboard_no]->getCustomKeyByID(i)->getKeyValueList()[0]->getSPKeyList()[0]!=0))
                pbtn->setStyleSheet("background-color: rgb(20, 150, 255);"); //blue for normal
            else
                pbtn->setStyleSheet(""); //none for unset
        }

    }

}



bool MainWindow::downloadToDevice(int keyboard_no){
    int result = -1;
    QMessageBox msg_info(this);
    msg_info.setWindowTitle(tr("Notice"));
    msg_info.setText(tr("Are you sure to download config to your device:") + ckb[keyboard_no]->getName()+"?");
    msg_info.setIcon(QMessageBox::Question);
    msg_info.setStandardButtons(QMessageBox::Ok | QMessageBox:: Cancel);
    if(msg_info.exec() == QMessageBox::Ok){
        QMessageBox msg_result(this);
        result = ckb[keyboard_no]->download(&table);
        if(result == 1){
            msg_result.setWindowTitle(tr("Notice"));
            msg_result.setText(tr("Download finished!"));
            msg_result.setIcon(QMessageBox::Information);
            msg_result.setStandardButtons(QMessageBox::Ok);
        }
        else if(result == -1){
            msg_result.setWindowTitle(tr("Error"));
            msg_result.setText(tr("Download Error :") + ckb[keyboard_no]->getLastError());
            msg_result.setIcon(QMessageBox::Critical);
            msg_result.setStandardButtons(QMessageBox::Ok);
        }
        else{
            msg_result.setWindowTitle(tr("Notice"));
            msg_result.setText(tr("Download finished! But there may be some errors."));
            msg_result.setIcon(QMessageBox::Information);
            msg_result.setStandardButtons(QMessageBox::Ok);
        }
        msg_result.exec();
    }
    return result;
};

bool MainWindow::addKeyValue(){
    //set append key value
    QVector<KeyValue*> temp_list = ckb[cur_keyboard_no]->getCustomKeyByID(cur_edit_key_no)->getKeyValueList();
    int temp_normal = 0;
    if(cur_key_normal.size() > 0)
        temp_normal = cur_key_normal[0];
    KeyValue *temp_kv = table.convertVector2KeyValue(temp_normal,cur_mouse,cur_media,cur_key_sp);
    temp_kv->setDelay(cur_delay);
    if(cur_mouse != 0 ){
        //add mouse key
        if(temp_list.size()>0 && (temp_list[0]->getNormalKeyIndex() !=0 ||  temp_list[0]->getMediaKeyIndex()!=0 || temp_list[0]->getMouseKeyIndex()!=0)){
            //mouse key is single can not be added
            QMessageBox msg_info(this);
            msg_info.setWindowTitle(tr("Notice"));
            msg_info.setText(tr("You can NOT add mouse event to Macro!"));
            msg_info.setIcon(QMessageBox::Critical);
            msg_info.setStandardButtons(QMessageBox::Ok);
            msg_info.exec();
        }
        else{
            //add to instant ckb and update ui
            ckb[cur_keyboard_no]->setKey(cur_edit_key_no,temp_kv);
            //update treeview
            QModelIndex temp_index = models[cur_keyboard_no]->index(cur_edit_key_no,0);
            models[cur_keyboard_no]->itemFromIndex(temp_index)->child(0,1)->setText(table.convertKeyValue2QString(temp_kv));
        }
    }
    else if(cur_media!=0){
        //add meida key
        if(temp_list.size()>0 && (temp_list[0]->getNormalKeyIndex() !=0 ||  temp_list[0]->getMediaKeyIndex()!=0 || temp_list[0]->getMouseKeyIndex()!=0)){
            //media key is single can not be added
            QMessageBox msg_info(this);
            msg_info.setWindowTitle(tr("Notice"));
            msg_info.setText(tr("You can NOT add meida key to Macro!"));
            msg_info.setIcon(QMessageBox::Critical);
            msg_info.setStandardButtons(QMessageBox::Ok);
            msg_info.exec();
        }
        else{
            //add to instant ckb and update ui
            ckb[cur_keyboard_no]->setKey(cur_edit_key_no,temp_kv);
            //update treeview
            QModelIndex temp_index = models[cur_keyboard_no]->index(cur_edit_key_no,0);
            models[cur_keyboard_no]->itemFromIndex(temp_index)->child(0,1)->setText(table.convertKeyValue2QString(temp_kv));
        }
    }
    else{
        //add normal key
        //justify whether there is any single key
        if(ckb[cur_keyboard_no]->getCustomKeyByID(cur_edit_key_no)->isMedia()||ckb[cur_keyboard_no]->getCustomKeyByID(cur_edit_key_no)->isMouse()){
            QMessageBox msg_info(this);
            msg_info.setWindowTitle(tr("Notice"));
            msg_info.setText(tr("You can NOT set MEDIA or MOUSE key to Macro!"));
            msg_info.setIcon(QMessageBox::Critical);
            msg_info.setStandardButtons(QMessageBox::Ok);
            msg_info.exec();
        }
        else{
            //special key justify
            if(ckb[cur_keyboard_no]->getCustomKeyByID(cur_edit_key_no)->getKeyValueList()[0]->getNormalKeyIndex() == 0 \
                    && ckb[cur_keyboard_no]->getCustomKeyByID(cur_edit_key_no)->getKeyValueList()[0]->getSPKeyList().size() > 0 \
                    && ckb[cur_keyboard_no]->getCustomKeyByID(cur_edit_key_no)->getKeyValueList()[0]->getSPKeyList()[0] == 0)
            {
                ckb[cur_keyboard_no]->setKey(cur_edit_key_no,temp_kv);
                //update treeview
                QModelIndex temp_index = models[cur_keyboard_no]->index(cur_edit_key_no,0);
                models[cur_keyboard_no]->itemFromIndex(temp_index)->child(0,1)->setText(table.convertKeyValue2QString(temp_kv));
            }
            else{
                if(ckb[cur_keyboard_no]->checkMacroAddable(cur_edit_key_no)){
                    //update to class
                    ckb[cur_keyboard_no]->appendKey(cur_edit_key_no,temp_kv);
                    //update treeview
                    QModelIndex temp_index = models[cur_keyboard_no]->index(cur_edit_key_no,0);
                    QList<QStandardItem*> kvs;
                    kvs.append(new QStandardItem(QString::number(temp_list.size()+1)));
                    kvs.append(new QStandardItem(table.convertKeyValue2QString(temp_kv)));
                    models[cur_keyboard_no]->itemFromIndex(temp_index)->appendRow(kvs);
                }
                else{
                    //can not add to macro because of hardware limit
                    QMessageBox msg_info(this);
                    msg_info.setWindowTitle(tr("Notice"));
                    msg_info.setText(tr("Can NOT add key macro : hardware limitation!"));
                    msg_info.setIcon(QMessageBox::Critical);
                    msg_info.setStandardButtons(QMessageBox::Ok);
                    msg_info.exec();
                }
            }
        }
    }

    //clear current stat
    ui->btn_setadd->hide();
    cur_key_sp.clear();
    cur_key_normal.clear();
    cur_mouse =0;
    cur_media =0;
    cur_delay =0;
    ui->btn_lshift->setStyleSheet("");
    ui->btn_lctrl->setStyleSheet("");
    ui->btn_lalt->setStyleSheet("");
    ui->btn_lwin->setStyleSheet("");
    ui->btn_rshift->setStyleSheet("");
    ui->btn_rctrl->setStyleSheet("");
    ui->btn_ralt->setStyleSheet("");
    ui->btn_rwin->setStyleSheet("");
    updateUI();

    return true;
}

bool MainWindow::deleteKeyValue(){
    //delet from current key
    if(ckb[cur_keyboard_no]->deleteTopKey(cur_edit_key_no)){
        //upaate treeview
        QModelIndex temp_index = models[cur_keyboard_no]->index(cur_edit_key_no,0);
        int list_size = ckb[cur_keyboard_no]->getCustomKeyByID(cur_edit_key_no)->getKeyValueCount();
        models[cur_keyboard_no]->itemFromIndex(temp_index)->removeRows(list_size,1);
    }
    else{
        qDebug() << "List is empty!";
        QModelIndex temp_index = models[cur_keyboard_no]->index(cur_edit_key_no,0);
        models[cur_keyboard_no]->itemFromIndex(temp_index)->child(0,1)->setText("None");
    }
    updateUI();
    return true;
}
MainWindow::~MainWindow()
{
    delete translator;
    delete ui;
}




