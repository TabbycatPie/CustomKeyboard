#include "customkey.h"

CustomKey::CustomKey(QString _name,QPushButton *mapping_key,bool _is_marco){
    this->name = _name;
    this->mapping_btn = mapping_key;
    this->is_marco = _is_marco;
}

void CustomKey::setKey(QVector<KeyValue*> _keys){
    if(keys.size()>1){
        //marco key
        is_marco = true;
    }
    else{
        is_marco = false;
    }
    this->keys =_keys;
};

QPushButton * CustomKey::getMappingButton(){
    return this->mapping_btn;
};
QString CustomKey::getName(){
    return this->name;
};
void CustomKey::setName(QString _name){
    this->name = _name;
}
bool CustomKey::isMarco(){
    return this->is_marco;
};

CustomKey::~CustomKey(){

};
