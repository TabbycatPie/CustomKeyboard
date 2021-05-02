#include "keyvalue.h"
#include <QVector>

KeyValue::KeyValue(int _normalkey,QVector<int> spkeys){
    this->normalkey = _normalkey;
    this->sp_keys = spkeys;
};

KeyValue::KeyValue(int _normalkey){
    this->normalkey = _normalkey;
    QVector<int> *temp = new QVector<int>();
    temp->append(0);
    this->sp_keys = *temp;
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
KeyValue::~KeyValue(){

};
