#include "customkeyboard.h"
#include "hidapi.h"
#include "hidcodetable.h"
#include <QPushButton>
#include <QVector>
#include <QString>

#include<QDebug>

//constructor of class CustomKeyboard
CustomKeyboard::CustomKeyboard(QString _name,int keynum,unsigned short pid,unsigned short vid,int marco_mem,int marco_spkey_mem,QPushButton *(*_btn_list)){
    this->name = _name;
    this->keynum = keynum;
    this->pid = pid;
    this->vid = vid;
    this->marco_mem = marco_mem;
    this->marco_spkey = marco_spkey_mem;
    this->last_error = "";

    this->normal_keycode = new uchar[keynum];
    this->spkey_mixcode = new uchar[keynum];

    for(int i =0;i<keynum;i++){
        this->key_list.append(new CustomKey("KEY"+QString::number(i+1),_btn_list[i],false));
    }
    //init memory
    for(int x = 0;x<keynum;x++){
        normal_keycode[x]=0x00;
        spkey_mixcode[x]=0x00;
    }

}
//------FUNCTIONS FOR KEY EDITING------//
void CustomKeyboard::setKey(int key_id, KeyValue *kv){
    this->key_list[key_id]->setKey(kv);
}
void CustomKeyboard::setKey(int key_id, QVector<KeyValue *> kvs){
    this->key_list[key_id]->setKey(kvs);
}
void CustomKeyboard::appendKey(int key_id,KeyValue *kv){
    this->key_list[key_id]->appendKey(kv);
}
bool CustomKeyboard::deleteTopKey(int key_id){
    return this->key_list[key_id]->deleteTopKey();
}

bool CustomKeyboard::checkMarcoAddable(int cur_key_no){

    int marco_count = 0;
    int sum_normal = 0;
    int sum_sp_key = 0;
    int sum_dely = 0;
    for(int i =0;i<getKeynum();i++){
        if(getCustomKeyByID(i)->isMarco()){
            marco_count++;
            QVector<KeyValue*> temp_list = getCustomKeyByID(i)->getKeyValueList();
            for(int j =0;j<temp_list.size();j++){
                //count normal key
                if(temp_list[j]->getNormalKeyIndex()!=0)
                    sum_normal++;
                //count special key
                if(temp_list[j]->getSPKeyList().size()>0 && temp_list[j]->getSPKeyList()[0]!=0)
                    sum_sp_key += temp_list[j]->getSPKeyList().size();
                if(temp_list[j]->getDelay()!=0)
                    sum_dely++;
            }
        }
    }
    //marco-key can only be less than 4
    if(marco_count>=4){
        if(!(getCustomKeyByID(cur_key_no)->isMarco() && marco_count ==4))
            return false;
    }
    //special-key can only be less than 10
    if(sum_sp_key>=10)
        return false;
    //delay-key can only be less than 10
    if(sum_dely>=10)
        return false;
    //normal-key can only be less than 40
    if(sum_normal>=40)
        return false;
    return true;
}
//-------------------------------------//
bool CustomKeyboard::download(HIDCodeTable *table){
    //open device
    hid_device *my_device;
    my_device = hid_open(vid,pid,NULL);
    if(my_device!=NULL){
        //open success,prepare data
        qDebug() << "device opened" <<endl;
        uchar frame_set_normal[65]={0x00};
        uchar frame_set_sp[65]={0x00};
        uchar frame_set_marco_status[65]={0x00};
        uchar frame_set_marco_index[65]={0x00};
        uchar frame_set_marco_sp_key[65]={0x00};
        uchar frame_set_marco_spkey_index[65]={0x00};
        uchar frame_set_marco[65]={0x00};
        uchar frame_set_mouse[65]={0x00};
        uchar frame_set_media[65]={0x00};
        uchar frame_set_delay[65]={0x00};
        uchar frame_set_delay_index[65]={0x00};

        QVector<uchar> temp_marco_buffer,temp_marco_index_buffer, //marco indecies and buffer
                       temp_marco_sp_buffer,temp_marco_sp_index,  //marco sp indecies and buffer
                       temp_delay_index,temp_delay_buffer;        //marco delay indecies ande buffer

        //initialize vector
        temp_marco_index_buffer.append(0x00);

        //set report ID = 0x00
        frame_set_normal           [0]= 0x00;
        frame_set_sp               [0]= 0x00;
        frame_set_marco_status     [0]= 0x00;
        frame_set_marco_index      [0]= 0x00;
        frame_set_marco_sp_key     [0]= 0x00;
        frame_set_marco_spkey_index[0]= 0x00;
        frame_set_marco            [0]= 0x00;
        frame_set_mouse            [0]= 0x00;
        frame_set_media            [0]= 0x00;
        frame_set_delay            [0]= 0x00;
        frame_set_delay_index      [0]= 0x00;

        //set frame header
        frame_set_normal           [1]= 0x01;   // set KEY_CODE          [10]
        frame_set_sp               [1]= 0x02;   // set SP_KEY_CODE       [10]
        frame_set_marco_status     [1]= 0x03;   // set KEY_MARCO         [2]
        frame_set_marco_index      [1]= 0x04;   // set MARCO_SPLIT_INDX  [5]
        frame_set_marco_sp_key     [1]= 0x05;   // set MARCO_SPE_KEYCODE [10]
        frame_set_marco_spkey_index[1]= 0x06;   // set MARCO_SPE_KEYINDX [10]
        frame_set_marco            [1]= 0x07;   // set MARCO_KEYCODE     [40]
        frame_set_mouse            [1]= 0x08;   // set MOUSE_CODE        [10]
        frame_set_media            [1]= 0x09;   // set MEDIA_CODE        [10]
        frame_set_delay            [1]= 0x0a;   // set MARCO_DELAY       [10]
        frame_set_delay_index      [1]= 0x0b;   // set MARCO_DELAY_INDX  [10]

        //generate frames
        for(int i = 0;i<this->getKeynum();i++){
            uchar temp_normal = 0x00;   //normal
            uchar temp_sp = 0x00;       //specoal
            uchar temp_mouse = 0x00;    //mouse
            uchar temp_media = 0x00;    //media
            if(!this->getCustomKeyByID(i)->isMarco()){
                //normal key
                table->convertNormaltKeyValue2Hex(&temp_normal,&temp_sp,this->getCustomKeyByID(i)->getKeyValueList()[0]);
                //single key
                temp_mouse = table->getHex(getCustomKeyByID(i)->getKeyValueList()[0]->getMouseKeyIndex());
                temp_media = table->getHex(getCustomKeyByID(i)->getKeyValueList()[0]->getMediaKeyIndex());
            }
            else{
                //set one marco key to temp buffer
                QVector<KeyValue*> tkvs = this->getCustomKeyByID(i)->getKeyValueList();
                for(int x =0;x<tkvs.size();x++){
                    uchar normal = 0x00;
                    uchar special = 0x00;
                    uchar delay = 0x00;
                    table->convertNormaltKeyValue2Hex(&normal,&special,this->getCustomKeyByID(i)->getKeyValueList()[x]);
                    delay = getCustomKeyByID(i)->getKeyValueList()[x]->getDelay();
                    //set normal key buffer
                    temp_marco_buffer.append(normal);
                    //set special key buffer
                    if(special!=0x00){
                        temp_marco_sp_buffer.append(special);
                        temp_marco_sp_index.append((uchar)(temp_marco_buffer.size()-1));
                    }
                    //set delay to key
                    if(delay!=0x00){
                        temp_delay_buffer.append(delay);
                        temp_delay_index.append((uchar)(temp_marco_buffer.size()-1));
                    }
                }
                temp_marco_index_buffer.append((uchar)temp_marco_buffer.size());
            }
            //construct normal key frame
            frame_set_mouse[i+2] = temp_mouse;
            frame_set_media[i+2] = temp_media;
            frame_set_normal[i+2] = temp_normal;
            frame_set_sp[i+2] = temp_sp;
        }
        //construct marco key frames
        //1.frame_set_marco_status
        uchar hi = 0x00;
        uchar lo = 0x00;
        //set low byte
        for(int i=0;i<9;i++){
            if(this->getCustomKeyByID(i)->isMarco()){
                lo|=(0x01<<i);
            }
        }
        //set high byte
        if(this->getKeynum()>8){
            for(int i=8;i<10;i++){
                if(this->getCustomKeyByID(i)->isMarco()){
                    hi|=(0x01<<(i-8));
                }
            }
        }
        //construct frame
        frame_set_marco_status[2] = hi;//set hi
        frame_set_marco_status[3] = lo;//set lo

        //set frame_set_marco_index
        int i = 1;
        for(;i<temp_marco_index_buffer.size();i++){
            frame_set_marco_index[i+2] = temp_marco_index_buffer[i];
        }
        for(;i<5;i++){
            frame_set_marco_index[i+2] = temp_marco_buffer.size();
        }
        //set frame_set_marco_sp_key
        for(int i =0;i<temp_marco_sp_buffer.size();i++){
            frame_set_marco_sp_key[i+2] = temp_marco_sp_buffer[i];
        }

        //set frame_set_marco_spkey_index
        for(int i =0;i<temp_marco_sp_index.size();i++){
            frame_set_marco_spkey_index[i+2] = temp_marco_sp_index[i];
        }

        //set frame_set_delay
        for(int i =0;i<temp_delay_buffer.size();i++){
            frame_set_delay[i+2] = temp_delay_buffer[i];
        }

        //set frame_set_delay_index
        for(int i =0;i<temp_delay_index.size();i++){
            frame_set_delay_index[i+2] = temp_delay_index[i];
        }

        //set frame_set_marco
        for(int i =0;i<temp_marco_buffer.size();i++){
            frame_set_marco[i+2] = temp_marco_buffer[i];
        }




        //send setting frames to device
        int res1 = hid_write(my_device, frame_set_normal, 65);  // -1 for error
        int res2 = hid_write(my_device, frame_set_sp, 65);      // -1 for error
        int res3 = hid_write(my_device,frame_set_marco_status,65);
        int res4 = hid_write(my_device,frame_set_marco_index,65);
        int res5 = hid_write(my_device,frame_set_marco_sp_key,65);
        int res6 = hid_write(my_device,frame_set_marco_spkey_index,65);
        int res8 = hid_write(my_device,frame_set_mouse,65);
        int res9 = hid_write(my_device,frame_set_media,65);
        int res10= hid_write(my_device,frame_set_delay,65);
        int res11= hid_write(my_device,frame_set_delay_index,65);
        int res7 = hid_write(my_device,frame_set_marco,65);

        if(res1 != -1 && res2 != -1 && res3!= -1 && res4 != -1 && res5 != -1
                && res6 != -1 && res7 != -1 && res8 != -1 && res9 !=-1 && res10 != -1
                && res11!= -1)
        {
            qDebug() << "Sending Successfully!" << endl;
            hid_close(my_device);
            return true;
        }else{
            last_error = "数据发送时发生错误!";
            QString text = QString::fromWCharArray(hid_error(my_device));
            qDebug() << "Sending Failed! Error:"<< text << endl;
            hid_close(my_device);
            return false;
        }
    }
    else{
        last_error = "未找到设备，设备未插入？";
        return false;
    }
}
QString CustomKeyboard::getLastError(){
    QString temp  = last_error;
    this->last_error = "";
    return temp;
}
QString CustomKeyboard::getName(){
    return this->name;
}
QPushButton * CustomKeyboard::getButtonByID(int key_no){
    return this->key_list.at(key_no)->getMappingButton();
}

uint16_t CustomKeyboard::getPid(){
    return this->pid;
}
uint16_t CustomKeyboard::getVid(){
    return this->vid;
}
int CustomKeyboard::getKeynum(){
    return this->keynum;
}
int CustomKeyboard::getMarcoMem(){
    return this->marco_mem;
}
int CustomKeyboard:: getMarcoSPkeyMem(){
    return this->marco_spkey;
}
CustomKey* CustomKeyboard::getCustomKeyByID(int key_no){
    return this->key_list[key_no];
};
CustomKeyboard::~CustomKeyboard(){
    delete this->normal_keycode;
    delete this->spkey_mixcode;
    qDeleteAll(this->key_list);
}

