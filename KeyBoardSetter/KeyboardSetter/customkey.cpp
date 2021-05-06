#include "customkey.h"
#include "keyvalue.h"

CustomKey::CustomKey(QString _name,QPushButton *mapping_key,bool _is_marco){
    this->name = _name;
    this->mapping_btn = mapping_key;
    this->is_marco = _is_marco;
    setKey(new KeyValue(0));
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
void CustomKey::appendKey(KeyValue* _key){
    keys.append(_key);
    if(keys.size()>1){
        //marco key
        is_marco = true;
    }
    else{
        is_marco = false;
    }
};
bool CustomKey::deleteTopKey(){
    if(keys.size()==1){
        if(keys[0]!=0){
            QVector<int> t;
            t.append(0);
            keys[0]->setValue(0,t);
            return false;
        }else
            return false;
    }
    else{
        keys.pop_back();
        return true;
    }
};
void CustomKey::setKey(KeyValue *_key){
    this->is_marco = false;
    this->keys.clear();
    this->keys.append(_key);
}

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
int CustomKey::getKeyValueCount(){
    return this->keys.size();
};

QVector<KeyValue*> CustomKey::getKeyValueList(){
    return this->keys;
};

CustomKey::~CustomKey(){

};
