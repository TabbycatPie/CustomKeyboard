#include "customkey.h"
#include "keyvalue.h"

CustomKey::CustomKey(QString _name,QPushButton *mapping_key,bool _is_marco=false){
    this->name = _name;
    this->mapping_btn = mapping_key;
    this->is_marco = _is_marco;
    setKey(new KeyValue(0));
}

void CustomKey::setKey(QVector<KeyValue*> _keys){
    //auto justify the key's type
    if(keys.size()>1){
        //marco key ,because of the vector's size is larger than one
        is_marco = true;
        is_mouse = false;
        is_media = false;
    }
    else{
        //this is not a marco key,because there is only one keyvalue in the vector
        is_marco = false;
        if(_keys[0]->getMediaKeyIndex()!=0){
            //this is a media key
            is_media = true;
            is_mouse = false;
        }
        else if(_keys[0]->getMouseKeyIndex()!=0){
            //this is a mouse key
            is_mouse = true;
            is_media = false;
        }
        else{
            //this is a normal key
            is_mouse = false;
            is_media = false;
        }
    }
    this->keys =_keys;
};
void CustomKey::appendKey(KeyValue* _key){
    keys.append(_key);
    if(keys.size()>1){
        //marco key
        is_marco = true;
        is_media = false;
        is_mouse = false;
    }
    else{
        //this is not a marco key,because there is only one keyvalue in the vector
        is_marco = false;
        if(_key->getMediaKeyIndex()!=0){
            //this is a media key
            is_media = true;
            is_mouse = false;
        }
        else if(_key->getMouseKeyIndex()!=0){
            //this is a mouse key
            is_mouse = true;
            is_media = false;
        }
        else{
            //this is a normal key
            is_mouse = false;
            is_media = false;
        }
    }
};
bool CustomKey::deleteTopKey(){
    if(keys.size()==1){
        if(keys[0]!=0){
            QVector<int> t;
            t.append(0);
            keys[0]->setValue(0,0,0,t);
            ////return to normal key
            this->is_marco = false;
            this->is_mouse = false;
            this->is_media = false;
        }
        return false;
    }
    else{
        keys.pop_back();
        if(keys.size() == 1){
            ////return to normal key
            this->is_marco = false;
            this->is_mouse = false;
            this->is_media = false;
        }
        return true;
    }
};
void CustomKey::setKey(KeyValue *_key){
    //this is not a marco key,because there is only one keyvalue in the vector
    is_marco = false;
    if(_key->getMediaKeyIndex()!=0){
        //this is a media key
        is_media = true;
        is_mouse = false;
    }
    else if(_key->getMouseKeyIndex()!=0){
        //this is a mouse key
        is_mouse = true;
        is_media = false;
    }
    else{
        //this is a normal key
        is_mouse = false;
        is_media = false;
    }
    //clear this and append new
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
bool CustomKey::isMouse(){
    return this->is_mouse;
};
bool CustomKey::isMedia(){
    return this->is_media;
};
int CustomKey::getKeyValueCount(){
    return this->keys.size();
};

QVector<KeyValue*> CustomKey::getKeyValueList(){
    return this->keys;
};

CustomKey::~CustomKey(){

};
