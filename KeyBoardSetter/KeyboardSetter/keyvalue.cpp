#include "keyvalue.h"

KeyValue::KeyValue(int _normalkey,QVector<int> spkeys){
    this->normalkey = _normalkey;
    this->sp_keys = spkeys;
};

void KeyValue::setValue(int _normalkey,QVector<int> spkeys){
    this->normalkey = _normalkey;
    this->sp_keys.clear();
    this->sp_keys = spkeys;
};

int KeyValue::getNormalKeyIndex(){
    return this->normalkey;
};
QVector<int> KeyValue::getSPKeyList(){
    return this->sp_keys;
};
