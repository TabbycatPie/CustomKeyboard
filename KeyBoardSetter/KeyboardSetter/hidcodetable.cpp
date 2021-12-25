#include "hidcodetable.h"


//public key board string
static const QString _key_string[]={
    "None",
    //normal keys
    "Escape","F1","F2","F3","F4","F5","F6","F7","F8","F9","F10","F11","F12",
    "`","1","2","3","4","5","6","7","8","9","0","-","+","Backspace",
    "Tab","Q","W","E","R","T","Y","U","I","O","P","[","]","\\",
    "Caps Lock","A","S","D","F","G","H","J","K","L",";","\'","Enter",
    "LShift","Z","X","C","V","B","N","M","<",">","/","RShift",
    "LCtrl","LWin","LAlt","Space","RAlt","RWin","RCtrl",
    //right area keys
    "Print Screen","Scroll Lock","Pause",
    "Insert","Home","PageUp",
    "Delete","End","PageDown",
    "Arrow UP","Arrow Left","Arrow Down","Arrow Right",
    //keypad
    "Num Lock","/(p)","*(p)","-(p)",
    "7(p)","8(p)","9(p)","+(p)",
    "4(p)","5(p)","6(p)",
    "1(p)","2(p)","3(p)","Enter(p)",
    "0(p)",".(p)",
    //mouse keys
    "LMouse","MMouse","RMouse",
    //multi-media keys
    "VolumeDown","VolumeUp","Play/Pause","LastSong","NextSong","Mute","Calculator",
    //f13~f24
    "F13","F14","F15","F16","F17","F18",
    "F19","F20","F21","F22","F23","F24"

};
//public key board name
static const QString _key_name[]={
    "None",
    //normal keys
    "Esc","F1","F2","F3","F4","F5","F6","F7","F8","F9","F10","F11","F12",
    "`~","1!","2@","3#","4$","5%","6^","7&&","8*","9(","0)","-_","=+","Backspace",
    "Tab","Q","W","E","R","T","Y","U","I","O","P","[{","]}","\\|",
    "Caps","A","S","D","F","G","H","J","K","L",";:","\'\"","Enter",
    "Shift","Z","X","C","V","B","N","M","<,",">.","/?","Shift",
    "Ctrl","Win","Alt","Space","Alt","Win","Ctrl",
    //right area keys
    "PtSr","ScLk","Paus",
    "Ins","Hom","PUp",
    "Del","End","PDwn",
    "↑","←","↓","→",
    //keypad
    "NumL","/","*","-",
    "7","8","9","+",
    "4","5","6",
    "1","2","3","Enter",
    "0",".",
    //mouse keys
    "LMouse","MMouse","RMouse",
    //multi-media keys
    "VolumeDown","VolumeUp","Play/Pause","LastSong","NextSong","Mute","Calculator",
    //f13~f24
    "F13","F14","F15","F16","F17","F18",
    "F19","F20","F21","F22","F23","F24"

};
//public key hex
static const uchar _key_hex[]={
    0x00,
    0x29,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,0x40,0x41,0x42,0x43,0x44,0x45,
    0x35,0x1e,0x1f,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x2d,0x2e,0x2a,
    0x2b,0x14,0x1a,0x08,0x15,0x17,0x1c,0x18,0x0c,0x12,0x13,0x2f,0x30,0x31,
    0x39,0x04,0x16,0x07,0x09,0x0a,0x0b,0x0d,0x0e,0x0f,0x33,0x34,0x28,
    /*Lshift*/0x02,0x1d,0x1b,0x06,0x19,0x05,0x11,0x10,0x36,0x37,0x38,/*Rshift*/0x20,
    /*Lctrl*/ 0x01,0x08,0x04,0x2c,0x40,0x80,0x10,
    //right area keys
    0x46,0x47,0x48,
    0x49,0x4a,0x4b,
    0x4c,0x4d,0x4e,
    0x52,0x50,0x51,0x4f,
    //keypad keys
    0x53,0x54,0x55,0x56,
    0x5f,0x60,0x61,0x57,
    0x5c,0x5d,0x5e,
    0x59,0x5a,0x5b,0x58,
    0x62,0x63,
    //mouse keys
    /*Left*/0x01,/*Middle*/0x04,/*Right*/0x02,
    //multi-media kes
    /*VolumeDown*/0x01,/*VolumeUp*/0x02,/*PlayPause*/0x04,/*LastSong*/0x08,/*NextSong*/0x10,/*Mute*/0x20,/*Calculator*/0x40,
    //f13~f24
    0x68,0x69,0x6a,0x6b,0x6c,0x6d,
    0x6e,0x6f,0x70,0x71,0x72,0x73
};

#define SPKEYY_NUM 8
static const int _spkey_index[]={
    /*Left Shift*/55,/*Right Shift*/66,/*Left Ctrl*/67,/*Left Win*/68,/*Left Alt*/69,
    /*Right Alt*/71,/*Right Win*/72,/*Right Ctrl*/73
};

#define MOUSEKEY_NUM 3
static const int _mousekey_index[]={
    104,105,106
};

#define MEDIAKEY_NUM 7
static const int _mediakey_index[]={
    107,108,109,110,111,112,113
};


HIDCodeTable::HIDCodeTable()
{
    this->key_string = _key_string;
    this->key_name = _key_name;
    this->key_hex = _key_hex;
    this->spkey_index = _spkey_index;
    this->media_index = _mediakey_index;
    this->mouse_index = _mousekey_index;
}

bool HIDCodeTable::isSPkey(int key_no){
    for(int i =0;i<SPKEYY_NUM;i++){
        if(spkey_index[i]==key_no)
            return true;
    }
    return false;
}
bool HIDCodeTable::isMouseKey(int key_no){
    for(int i =0;i<MOUSEKEY_NUM;i++){
        if(mouse_index[i]==key_no)
            return true;
    }
    return false;
};
bool HIDCodeTable::isMediaKey(int key_no){
    for(int i =0;i<MEDIAKEY_NUM;i++){
        if(media_index[i]==key_no)
            return true;
    }
    return false;
};

QString HIDCodeTable::getKeyString(int key_no){
    return this->key_string[key_no];
}

QString HIDCodeTable::getButtonNmae(int key_no)
{
    return this->key_name[key_no];
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
KeyValue* HIDCodeTable::convertVector2KeyValue(int normal,int mouse,int media,const QVector<int> sp_keys){
    return new KeyValue(normal,mouse,media,sp_keys);
};
QString HIDCodeTable::convertKeyValue2QString(KeyValue *kv){
    QString out ="";
    if(kv->getDelay()>0){
        out = "Delay " + QString::number(kv->getDelay()/10.0f)+"s + ";
    }
    if(kv->getSPKeyList().size()>0 && kv->getSPKeyList()[0]!=0){
        out += getKeyString(kv->getSPKeyList()[0]);
        for(int i =1;i<kv->getSPKeyList().size();i++){
            out += " + " + getKeyString(kv->getSPKeyList()[i]);
        }
        if(kv->getNormalKeyIndex()!=0)
            out += " + " + getKeyString(kv->getNormalKeyIndex());
    }
    else{
        int temp = 0;
        if(kv->getMediaKeyIndex()!=0)
            temp = kv->getMediaKeyIndex();
        if(kv->getMouseKeyIndex()!=0)
            temp =kv->getMouseKeyIndex();
        if(kv->getNormalKeyIndex()!=0)
            temp = kv->getNormalKeyIndex();
        out += getKeyString(temp);
    }
    return out;
}
int HIDCodeTable::getSPkeybByindex(int x)
{
    return  this->spkey_index[x];
};
HIDCodeTable::~HIDCodeTable(){

};
