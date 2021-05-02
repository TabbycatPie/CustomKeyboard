#include "customkeyboard.h"
#include <QPushButton>
#include <QVector>
#include <QString>

//constructor of class CustomKeyboard
CustomKeyboard::CustomKeyboard(QString _name,int keynum,uint16_t pid,uint16_t vid,int marco_mem,int marco_spkey_mem,QPushButton *(*_btn_list)){
    this->name = _name;
    this->keynum = keynum;
    this->pid = pid;
    this->vid = vid;
    this->marco_mem = marco_mem;
    this->marco_spkey = marco_spkey_mem;

    this->normal_keycode = new uchar[keynum];
    this->spkey_mixcode = new uchar[keynum];

    for(int i =0;i<keynum;i++){
        this->key_list.append(new CustomKey("KEY"+QString::number(i),_btn_list[i],false));
    }
    //init memory
    for(int x = 0;x<keynum;x++){
        normal_keycode[x]=0x00;
        spkey_mixcode[x]=0x00;
    }

}
void CustomKeyboard::setKey(int key_id, KeyValue kv){
    this->key_list[key_id]->setKey(&kv);
}

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

CustomKeyboard::~CustomKeyboard(){
    delete this->normal_keycode;
    delete this->spkey_mixcode;
    qDeleteAll(this->key_list);
}
