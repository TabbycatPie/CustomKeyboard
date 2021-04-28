#include "customkeyboard.h"

//constructor of class CustomKeyboard
CustomKeyboard::CustomKeyboard(int keynum,uint16_t pid,uint16_t vid,int marco_mem,int marco_spkey_mem){
    this->keynum = keynum;
    this->pid = pid;
    this->vid = vid;
    this->marco_mem = marco_mem;
    this->marco_spkey = marco_spkey_mem;

    this->normal_keycode = new uchar[keynum];
    this->spkey_mixcode = new uchar[keynum];
    //init memory
    for(int x = 0;x<keynum;x++){
        normal_keycode[x]=0x00;
        spkey_mixcode[x]=0x00;
    }


}

void CustomKeyboard::setNormalKey(int setkey_no, uchar keytable_no, uchar spkeytable_no){
    this->normal_keycode[++setkey_no] = keytable_no;
    this->spkey_mixcode[++setkey_no]  = spkeytable_no;
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
}
