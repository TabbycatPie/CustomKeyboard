#include "hidcodetable.h"


//public key board string
static QString _key_string[126];
//public key board name
static QString _key_name[126];
//public key hex
static uchar _key_hex[126];

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
    _key_name[0] = tr("None"); _key_string[0] = tr("None");_key_hex[0]=0x0;
    _key_name[1] = tr("Esc"); _key_string[1] = tr("Escape");_key_hex[1]=0x29;
    _key_name[2] = tr("F1"); _key_string[2] = tr("F1");_key_hex[2]=0x3a;
    _key_name[3] = tr("F2"); _key_string[3] = tr("F2");_key_hex[3]=0x3b;
    _key_name[4] = tr("F3"); _key_string[4] = tr("F3");_key_hex[4]=0x3c;
    _key_name[5] = tr("F4"); _key_string[5] = tr("F4");_key_hex[5]=0x3d;
    _key_name[6] = tr("F5"); _key_string[6] = tr("F5");_key_hex[6]=0x3e;
    _key_name[7] = tr("F6"); _key_string[7] = tr("F6");_key_hex[7]=0x3f;
    _key_name[8] = tr("F7"); _key_string[8] = tr("F7");_key_hex[8]=0x40;
    _key_name[9] = tr("F8"); _key_string[9] = tr("F8");_key_hex[9]=0x41;
    _key_name[10] = tr("F9"); _key_string[10] = tr("F9");_key_hex[10]=0x42;
    _key_name[11] = tr("F10"); _key_string[11] = tr("F10");_key_hex[11]=0x43;
    _key_name[12] = tr("F11"); _key_string[12] = tr("F11");_key_hex[12]=0x44;
    _key_name[13] = tr("F12"); _key_string[13] = tr("F12");_key_hex[13]=0x45;
    _key_name[14] = tr("`~"); _key_string[14] = tr("`");_key_hex[14]=0x35;
    _key_name[15] = tr("1!"); _key_string[15] = tr("1");_key_hex[15]=0x1e;
    _key_name[16] = tr("2@"); _key_string[16] = tr("2");_key_hex[16]=0x1f;
    _key_name[17] = tr("3#"); _key_string[17] = tr("3");_key_hex[17]=0x20;
    _key_name[18] = tr("4$"); _key_string[18] = tr("4");_key_hex[18]=0x21;
    _key_name[19] = tr("5%"); _key_string[19] = tr("5");_key_hex[19]=0x22;
    _key_name[20] = tr("6^"); _key_string[20] = tr("6");_key_hex[20]=0x23;
    _key_name[21] = tr("7&&"); _key_string[21] = tr("7");_key_hex[21]=0x24;
    _key_name[22] = tr("8*"); _key_string[22] = tr("8");_key_hex[22]=0x25;
    _key_name[23] = tr("9("); _key_string[23] = tr("9");_key_hex[23]=0x26;
    _key_name[24] = tr("0)"); _key_string[24] = tr("0");_key_hex[24]=0x27;
    _key_name[25] = tr("-_"); _key_string[25] = tr("-");_key_hex[25]=0x2d;
    _key_name[26] = tr("=+"); _key_string[26] = tr("+");_key_hex[26]=0x2e;
    _key_name[27] = tr("Backspace"); _key_string[27] = tr("Backspace");_key_hex[27]=0x2a;
    _key_name[28] = tr("Tab"); _key_string[28] = tr("Tab");_key_hex[28]=0x2b;
    _key_name[29] = tr("Q"); _key_string[29] = tr("Q");_key_hex[29]=0x14;
    _key_name[30] = tr("W"); _key_string[30] = tr("W");_key_hex[30]=0x1a;
    _key_name[31] = tr("E"); _key_string[31] = tr("E");_key_hex[31]=0x8;
    _key_name[32] = tr("R"); _key_string[32] = tr("R");_key_hex[32]=0x15;
    _key_name[33] = tr("T"); _key_string[33] = tr("T");_key_hex[33]=0x17;
    _key_name[34] = tr("Y"); _key_string[34] = tr("Y");_key_hex[34]=0x1c;
    _key_name[35] = tr("U"); _key_string[35] = tr("U");_key_hex[35]=0x18;
    _key_name[36] = tr("I"); _key_string[36] = tr("I");_key_hex[36]=0xc;
    _key_name[37] = tr("O"); _key_string[37] = tr("O");_key_hex[37]=0x12;
    _key_name[38] = tr("P"); _key_string[38] = tr("P");_key_hex[38]=0x13;
    _key_name[39] = tr("[{"); _key_string[39] = tr("[");_key_hex[39]=0x2f;
    _key_name[40] = tr("]}"); _key_string[40] = tr("]");_key_hex[40]=0x30;
    _key_name[41] = tr("\\|"); _key_string[41] = tr("\\");_key_hex[41]=0x31;
    _key_name[42] = tr("Caps"); _key_string[42] = tr("Caps Lock");_key_hex[42]=0x39;
    _key_name[43] = tr("A"); _key_string[43] = tr("A");_key_hex[43]=0x4;
    _key_name[44] = tr("S"); _key_string[44] = tr("S");_key_hex[44]=0x16;
    _key_name[45] = tr("D"); _key_string[45] = tr("D");_key_hex[45]=0x7;
    _key_name[46] = tr("F"); _key_string[46] = tr("F");_key_hex[46]=0x9;
    _key_name[47] = tr("G"); _key_string[47] = tr("G");_key_hex[47]=0xa;
    _key_name[48] = tr("H"); _key_string[48] = tr("H");_key_hex[48]=0xb;
    _key_name[49] = tr("J"); _key_string[49] = tr("J");_key_hex[49]=0xd;
    _key_name[50] = tr("K"); _key_string[50] = tr("K");_key_hex[50]=0xe;
    _key_name[51] = tr("L"); _key_string[51] = tr("L");_key_hex[51]=0xf;
    _key_name[52] = tr(";:"); _key_string[52] = tr(";");_key_hex[52]=0x33;
    _key_name[53] = tr("'\""); _key_string[53] = tr("'");_key_hex[53]=0x34;
    _key_name[54] = tr("Enter"); _key_string[54] = tr("Enter");_key_hex[54]=0x28;
    _key_name[55] = tr("Shift"); _key_string[55] = tr("LShift");_key_hex[55]=0x2;
    _key_name[56] = tr("Z"); _key_string[56] = tr("Z");_key_hex[56]=0x1d;
    _key_name[57] = tr("X"); _key_string[57] = tr("X");_key_hex[57]=0x1b;
    _key_name[58] = tr("C"); _key_string[58] = tr("C");_key_hex[58]=0x6;
    _key_name[59] = tr("V"); _key_string[59] = tr("V");_key_hex[59]=0x19;
    _key_name[60] = tr("B"); _key_string[60] = tr("B");_key_hex[60]=0x5;
    _key_name[61] = tr("N"); _key_string[61] = tr("N");_key_hex[61]=0x11;
    _key_name[62] = tr("M"); _key_string[62] = tr("M");_key_hex[62]=0x10;
    _key_name[63] = tr("<,"); _key_string[63] = tr("<");_key_hex[63]=0x36;
    _key_name[64] = tr(">."); _key_string[64] = tr(">");_key_hex[64]=0x37;
    _key_name[65] = tr("/?"); _key_string[65] = tr("/");_key_hex[65]=0x38;
    _key_name[66] = tr("Shift"); _key_string[66] = tr("RShift");_key_hex[66]=0x20;
    _key_name[67] = tr("Ctrl"); _key_string[67] = tr("LCtrl");_key_hex[67]=0x1;
    _key_name[68] = tr("Win"); _key_string[68] = tr("LWin");_key_hex[68]=0x8;
    _key_name[69] = tr("Alt"); _key_string[69] = tr("LAlt");_key_hex[69]=0x4;
    _key_name[70] = tr("Space"); _key_string[70] = tr("Space");_key_hex[70]=0x2c;
    _key_name[71] = tr("Alt"); _key_string[71] = tr("RAlt");_key_hex[71]=0x40;
    _key_name[72] = tr("Win"); _key_string[72] = tr("RWin");_key_hex[72]=0x80;
    _key_name[73] = tr("Ctrl"); _key_string[73] = tr("RCtrl");_key_hex[73]=0x10;
    _key_name[74] = tr("PtSr"); _key_string[74] = tr("Print Screen");_key_hex[74]=0x46;
    _key_name[75] = tr("ScLk"); _key_string[75] = tr("Scroll Lock");_key_hex[75]=0x47;
    _key_name[76] = tr("Paus"); _key_string[76] = tr("Pause");_key_hex[76]=0x48;
    _key_name[77] = tr("Ins"); _key_string[77] = tr("Insert");_key_hex[77]=0x49;
    _key_name[78] = tr("Hom"); _key_string[78] = tr("Home");_key_hex[78]=0x4a;
    _key_name[79] = tr("PUp"); _key_string[79] = tr("PageUp");_key_hex[79]=0x4b;
    _key_name[80] = tr("Del"); _key_string[80] = tr("Delete");_key_hex[80]=0x4c;
    _key_name[81] = tr("End"); _key_string[81] = tr("End");_key_hex[81]=0x4d;
    _key_name[82] = tr("PDwn"); _key_string[82] = tr("PageDown");_key_hex[82]=0x4e;
    _key_name[83] = tr("↑"); _key_string[83] = tr("Arrow UP");_key_hex[83]=0x52;
    _key_name[84] = tr("←"); _key_string[84] = tr("Arrow Left");_key_hex[84]=0x50;
    _key_name[85] = tr("↓"); _key_string[85] = tr("Arrow Down");_key_hex[85]=0x51;
    _key_name[86] = tr("→"); _key_string[86] = tr("Arrow Right");_key_hex[86]=0x4f;
    _key_name[87] = tr("NumL"); _key_string[87] = tr("Num Lock");_key_hex[87]=0x53;
    _key_name[88] = tr("/"); _key_string[88] = tr("/(p)");_key_hex[88]=0x54;
    _key_name[89] = tr("*"); _key_string[89] = tr("*(p)");_key_hex[89]=0x55;
    _key_name[90] = tr("-"); _key_string[90] = tr("-(p)");_key_hex[90]=0x56;
    _key_name[91] = tr("7"); _key_string[91] = tr("7(p)");_key_hex[91]=0x5f;
    _key_name[92] = tr("8"); _key_string[92] = tr("8(p)");_key_hex[92]=0x60;
    _key_name[93] = tr("9"); _key_string[93] = tr("9(p)");_key_hex[93]=0x61;
    _key_name[94] = tr("+"); _key_string[94] = tr("+(p)");_key_hex[94]=0x57;
    _key_name[95] = tr("4"); _key_string[95] = tr("4(p)");_key_hex[95]=0x5c;
    _key_name[96] = tr("5"); _key_string[96] = tr("5(p)");_key_hex[96]=0x5d;
    _key_name[97] = tr("6"); _key_string[97] = tr("6(p)");_key_hex[97]=0x5e;
    _key_name[98] = tr("1"); _key_string[98] = tr("1(p)");_key_hex[98]=0x59;
    _key_name[99] = tr("2"); _key_string[99] = tr("2(p)");_key_hex[99]=0x5a;
    _key_name[100] = tr("3"); _key_string[100] = tr("3(p)");_key_hex[100]=0x5b;
    _key_name[101] = tr("Enter"); _key_string[101] = tr("Enter(p)");_key_hex[101]=0x58;
    _key_name[102] = tr("0"); _key_string[102] = tr("0(p)");_key_hex[102]=0x62;
    _key_name[103] = tr("."); _key_string[103] = tr(".(p)");_key_hex[103]=0x63;
    _key_name[104] = tr("LMouse"); _key_string[104] = tr("LMouse");_key_hex[104]=0x1;
    _key_name[105] = tr("MMouse"); _key_string[105] = tr("MMouse");_key_hex[105]=0x4;
    _key_name[106] = tr("RMouse"); _key_string[106] = tr("RMouse");_key_hex[106]=0x2;
    _key_name[107] = tr("VolumeDown"); _key_string[107] = tr("VolumeDown");_key_hex[107]=0x1;
    _key_name[108] = tr("VolumeUp"); _key_string[108] = tr("VolumeUp");_key_hex[108]=0x2;
    _key_name[109] = tr("Play/Pause"); _key_string[109] = tr("Play/Pause");_key_hex[109]=0x4;
    _key_name[110] = tr("LastSong"); _key_string[110] = tr("LastSong");_key_hex[110]=0x8;
    _key_name[111] = tr("NextSong"); _key_string[111] = tr("NextSong");_key_hex[111]=0x10;
    _key_name[112] = tr("Mute"); _key_string[112] = tr("Mute");_key_hex[112]=0x20;
    _key_name[113] = tr("Calculator"); _key_string[113] = tr("Calculator");_key_hex[113]=0x40;
    _key_name[114] = tr("F13"); _key_string[114] = tr("F13");_key_hex[114]=0x68;
    _key_name[115] = tr("F14"); _key_string[115] = tr("F14");_key_hex[115]=0x69;
    _key_name[116] = tr("F15"); _key_string[116] = tr("F15");_key_hex[116]=0x6a;
    _key_name[117] = tr("F16"); _key_string[117] = tr("F16");_key_hex[117]=0x6b;
    _key_name[118] = tr("F17"); _key_string[118] = tr("F17");_key_hex[118]=0x6c;
    _key_name[119] = tr("F18"); _key_string[119] = tr("F18");_key_hex[119]=0x6d;
    _key_name[120] = tr("F19"); _key_string[120] = tr("F19");_key_hex[120]=0x6e;
    _key_name[121] = tr("F20"); _key_string[121] = tr("F20");_key_hex[121]=0x6f;
    _key_name[122] = tr("F21"); _key_string[122] = tr("F21");_key_hex[122]=0x70;
    _key_name[123] = tr("F22"); _key_string[123] = tr("F22");_key_hex[123]=0x71;
    _key_name[124] = tr("F23"); _key_string[124] = tr("F23");_key_hex[124]=0x72;
    _key_name[125] = tr("F24"); _key_string[125] = tr("F24");_key_hex[125]=0x73;
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
        out = tr("Delay ") + QString::number(kv->getDelay()/10.0f)+"s + ";
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
