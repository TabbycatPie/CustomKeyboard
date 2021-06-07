#include "keyvalue.h"
#include <QJsonArray>
#include <QVector>

KeyValue::KeyValue(int _normalkey,int _mousekey,int _mediakey,QVector<int> spkeys){
    this->normalkey = _normalkey;
    this->sp_keys = spkeys;
    this->mousekey = _mousekey;
    this->mediakey = _mediakey;
    this->delay = 0x00;
};

KeyValue::KeyValue(int _normalkey){
    this->normalkey = _normalkey;
    QVector<int> *temp = new QVector<int>();
    temp->append(0);
    this->sp_keys = *temp;
    this->mediakey = 0;
    this->mousekey = 0;
    this->delay = 0x00;
};

void KeyValue::setValue(int _normalkey,int _mousekey,int _mediakey,QVector<int> spkeys){
    this->normalkey = _normalkey;
    this->sp_keys.clear();
    this->sp_keys = spkeys;
    this->mousekey = _mousekey;
    this->mediakey = _mediakey;
};
uchar KeyValue::getDelay(){
    return this->delay;
};
void KeyValue::setDelay(uchar _delay){
    this->delay = _delay;
};
int KeyValue::getNormalKeyIndex(){
    return this->normalkey;
};
int KeyValue::getMouseKeyIndex(){
    return this->mousekey;
};
int KeyValue::getMediaKeyIndex(){
    return this->mediakey;
};
QVector<int> KeyValue::getSPKeyList(){
    return this->sp_keys;
}

QJsonObject KeyValue::toJsonObj()
{
    QJsonObject kvjson = QJsonObject();
    QJsonArray sparray = QJsonArray();
    //generate json
    kvjson.insert("mouse_key_index",this->mousekey);
    kvjson.insert("media_key_index",this->mediakey);
    kvjson.insert("normal_key_index",this->normalkey);
    kvjson.insert("delay",this->delay);
    for(int i = 0; i< this->sp_keys.size();i++){
        sparray.append(sp_keys[i]);
    }
    kvjson.insert("sp_key_list",sparray);
    return kvjson;
};
KeyValue::~KeyValue(){

};
