#include "customkeyboard.h"
#include "hidapi.h"
#include <QPushButton>
#include <QVector>
#include <QString>

#include<QDebug>

//constructor of class CustomKeyboard
CustomKeyboard::CustomKeyboard(QString _name,int keynum,unsigned short pid,unsigned short vid,int marco_mem,int marco_spkey_mem,QPushButton *(*_btn_list)){
    this->name = _name;
    this->keynum = keynum;
    this->pid = pid;
    this->vid = vid;
    this->marco_mem = marco_mem;
    this->marco_spkey = marco_spkey_mem;
    this->last_error = "";

    this->normal_keycode = new uchar[keynum];
    this->spkey_mixcode = new uchar[keynum];

    for(int i =0;i<keynum;i++){
        this->key_list.append(new CustomKey("KEY"+QString::number(i+1),_btn_list[i],false));
    }
    //init memory
    for(int x = 0;x<keynum;x++){
        normal_keycode[x]=0x00;
        spkey_mixcode[x]=0x00;
    }

}
void CustomKeyboard::setKey(int key_id, KeyValue *kv){
    this->key_list[key_id]->setKey(kv);
}
bool CustomKeyboard::download(){
    //open device
    hid_device *my_device;
    my_device = hid_open(vid,pid,NULL);
    if(my_device!=NULL){
        //open success,start transfer
        int res;	// -1 for error
        unsigned char buf[65];
        buf[0] = 0x00;	// Report ID
        for(unsigned int i = 0;i<65;i++){
            buf[i]=i;
        }
        buf[1] = 0x00;
        buf[2] = 0x04;

        res = hid_write(my_device, buf, 65);
        if(res != -1){
            qDebug() << "Sending Successfully!" << endl;
        }else{
            last_error = "Data sending is failed!";
            qDebug() << "Sending Failed!" << endl;
            hid_close(my_device);
        }
    }
    else{
        last_error = "Can not open device!";
        return false;
    }
};
QString CustomKeyboard::getLastError(){
    QString temp  = last_error;
    this->last_error = "";
    return temp;
};
QString CustomKeyboard::getName(){
    return this->name;
}
QPushButton * CustomKeyboard::getButtonByID(int key_no){
    return this->key_list.at(key_no)->getMappingButton();
}

uint16_t CustomKeyboard::getPid(){
    return this->pid;
}
uint16_t CustomKeyboard::getVid(){
    return this->vid;
}
int CustomKeyboard::getKeynum(){
    return this->keynum;
}
int CustomKeyboard::getMarcoMem(){
    return this->marco_mem;
}
int CustomKeyboard:: getMarcoSPkeyMem(){
    return this->marco_spkey;
}
CustomKey* CustomKeyboard::getCustomKeyByID(int key_no){
    return this->key_list[key_no];
};
CustomKeyboard::~CustomKeyboard(){
    delete this->normal_keycode;
    delete this->spkey_mixcode;
    qDeleteAll(this->key_list);
}

