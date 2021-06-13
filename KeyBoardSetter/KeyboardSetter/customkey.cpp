#include "customkey.h"
#include "keyvalue.h"

#include <qjsonarray.h>

CustomKey::CustomKey(QString _name,QPushButton *mapping_key,bool _is_macro=false){
    this->name = _name;
    this->mapping_btn = mapping_key;
    this->is_macro = _is_macro;
    setKey(new KeyValue(0));
}

void CustomKey::setKey(QVector<KeyValue*> _keys){
    //auto justify the key's type
    if(_keys.size()>1){
        //macro key ,because of the vector's size is larger than one
        is_macro = true;
        is_mouse = false;
        is_media = false;
    }
    else{
        //this is not a macro key,because there is only one keyvalue in the vector
        is_macro = false;
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
        //macro key
        is_macro = true;
        is_media = false;
        is_mouse = false;
    }
    else{
        //this is not a macro key,because there is only one keyvalue in the vector
        is_macro = false;
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
            keys[0]->setDelay(0);
            ////return to normal key
            this->is_macro = false;
            this->is_mouse = false;
            this->is_media = false;
        }
        return false;
    }
    else{
        keys.pop_back();
        if(keys.size() == 1){
            ////return to normal key
            this->is_macro = false;
            this->is_mouse = false;
            this->is_media = false;
        }
        return true;
    }
};
void CustomKey::setKey(KeyValue *_key){
    //this is not a macro key,because there is only one keyvalue in the vector
    is_macro = false;
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
bool CustomKey::isMacro(){
    return this->is_macro;
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
}

QJsonObject CustomKey::toJsonObj()
{
    QJsonObject ckjson = QJsonObject();
    ckjson.insert("name",this->name);
    ckjson.insert("is_macro",this->is_macro);
    ckjson.insert("is_mouse",this->is_mouse);
    ckjson.insert("is_media",this->is_media);
    //ckjson.insert("normalkey_index",this->normalkey_index);
    QJsonArray kvarray = QJsonArray();
    foreach(KeyValue *tempkv,this->keys){
        kvarray.append(tempkv->toJsonObj());
    }
    ckjson.insert("kv_list",kvarray);
    return ckjson;

}

CustomKey *CustomKey::fromJson(QJsonObject jsonobj,QPushButton *mapping_button)
{
    bool _is_macro = jsonobj.value("is_macro").toBool();
    QString _name = jsonobj.value("name").toString();
    QJsonArray jsonarray = jsonobj.value("kv_list").toArray();
    QVector<KeyValue*> *kv_list = new QVector<KeyValue*>();
    foreach(QJsonValue jsonvalue,jsonarray){
        KeyValue* kv = KeyValue::fromJson(jsonvalue.toObject());
        kv_list->append(kv);
    }
    CustomKey *ck = new CustomKey(_name,mapping_button,_is_macro);
    ck->setKey(*kv_list);
    return ck;
};

CustomKey::~CustomKey(){

}
