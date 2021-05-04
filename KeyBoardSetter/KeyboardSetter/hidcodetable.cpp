#include "hidcodetable.h"


//public key board string
static const QString _key_string[]={
    "None",
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
//public key hex
static const uchar _key_hex[]={
    0x00,
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
static const int _spkey_index[]={
    /*Left Shift*/55,/*Right Shift*/66,/*Left Ctrl*/67,/*Left Win*/68,/*Left Alt*/69,
    /*Right Alt*/71,/*Right Win*/72,/*Right Ctrl*/73
};


HIDCodeTable::HIDCodeTable()
{
    this->key_string = _key_string;
    this->key_hex = _key_hex;
    this->spkey_index = _spkey_index;
}

bool HIDCodeTable::isSPkey(int key_no){
    for(int i =0;i<8;i++){
        if(spkey_index[i]==key_no)
            return true;
    }
    return false;
}

QString HIDCodeTable::getKeyString(int key_no){
    return this->key_string[key_no];
};

uchar HIDCodeTable::getHex(int key_no){
    return this->key_hex[key_no];
};

uchar HIDCodeTable::getSpKeyHex(QVector<int> spkey_list){
    uchar temp = 0x00;
    for(int i =0;i<spkey_list.size();i++){
        temp |= this->getHex(spkey_list[i]);
    }
    return temp;
};

void HIDCodeTable::convertNormaltKeyValue2Hex(uchar * normal,uchar * sp_key,KeyValue *kv){
    *normal = getHex(kv->getNormalKeyIndex());
    *sp_key = getSpKeyHex(kv->getSPKeyList());
};
KeyValue* HIDCodeTable::convertVector2KeyValue(int normal,const QVector<int> sp_keys){
    return new KeyValue(normal,sp_keys);
};
QString HIDCodeTable::convertKeyValue2QString(KeyValue *kv){
    QString out ="";
    if(kv->getSPKeyList().size()>0 && kv->getSPKeyList()[0]!=0){
        out = getKeyString(kv->getSPKeyList()[0]);
        for(int i =1;i<kv->getSPKeyList().size();i++){
            out += " + " + getKeyString(kv->getSPKeyList()[i]);
        }
        if(kv->getNormalKeyIndex()!=0)
            out += " + " + getKeyString(kv->getNormalKeyIndex());
    }
    else{
        out = getKeyString(kv->getNormalKeyIndex());
    }
    return out;
};
HIDCodeTable::~HIDCodeTable(){

};
