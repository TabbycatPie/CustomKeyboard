#include "customkeyboard.h"
#include "hidapi.h"
#include "hidcodetable.h"
#include <QPushButton>
#include <QVector>
#include <QString>
#include <QThread>

#include<QDebug>
#include <qjsonarray.h>

//constructor of class CustomKeyboard
CustomKeyboard::CustomKeyboard(QString _name,int keynum,unsigned short pid,unsigned short vid,QPushButton *(*_btn_list)){
    this->name = _name;
    this->keynum = keynum;
    this->pid = pid;
    this->vid = vid;
    //set macro setting to default
    this->macro_mem = 34;
    this->macro_spkey = 10;
    this->macro_delay = 10;
    this->macro_key_count = 10;

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

CustomKeyboard::CustomKeyboard(QString _name, int keynum, unsigned short pid, unsigned short vid, QVector<QPushButton *> *btn_list)
{
    this->name = _name;
    this->keynum = keynum;
    this->pid = pid;
    this->vid = vid;
    //set macro setting to default
    this->macro_mem = 34;
    this->macro_spkey = 10;
    this->macro_delay = 10;
    this->macro_key_count = 10;

    this->last_error = "";

    this->normal_keycode = new uchar[keynum];
    this->spkey_mixcode = new uchar[keynum];

    for(int i =0;i<keynum;i++){
        this->key_list.append(new CustomKey("KEY"+QString::number(i+1),btn_list->data()[i],false));
    }
    //init memory
    for(int x = 0;x<keynum;x++){
        normal_keycode[x]=0x00;
        spkey_mixcode[x]=0x00;
    }
}
void CustomKeyboard::setMacroConfig(int mlen, int mcount, int mspkey, int mdelay)
{
    this->macro_mem = mlen;
    this->macro_key_count = mcount;
    this->macro_spkey = mspkey;
    this->macro_delay = mdelay;
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
void CustomKeyboard::setKeyList(QVector<CustomKey *> list)
{
    this->key_list.clear();
    this->key_list = list;
}
bool CustomKeyboard::deleteTopKey(int key_id){
    if(key_id >= 0 )
        return this->key_list[key_id]->deleteTopKey();
    else
        return false;
}
bool CustomKeyboard::checkMacroAddable(int cur_key_no){
    int macro_count = 0;
    int sum_normal = 0;
    int sum_sp_key = 0;
    int sum_dely = 0;
    for(int i =0;i<getKeynum();i++){
        if(getCustomKeyByID(i)->isMacro()){
            macro_count++;
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
    //macro-key can only be less than 4
    if(macro_count>=this->macro_key_count){
        if(!(getCustomKeyByID(cur_key_no)->isMacro() && macro_count ==this->macro_key_count))
            return false;
    }
    //special-key can only be less than 10
    if(sum_sp_key>=this->macro_spkey)
        return false;
    //delay-key can only be less than 10
    if(sum_dely>=this->macro_delay)
        return false;
    //normal-key can only be less than 34
    if(sum_normal>=this->macro_mem)
        return false;
    return true;
}
//-------------------------------------//
int CustomKeyboard::download(HIDCodeTable *table){
    //open device
    hid_device *my_device;
    my_device = hid_open(vid,pid,nullptr);
    if(my_device!=NULL){
        //open success,prepare data
        qDebug() << "device opened" <<endl;
        uchar frame_set_normal[65]={0x00};
        uchar frame_set_sp[65]={0x00};
        uchar frame_set_macro_status[65]={0x00};
        uchar frame_set_macro_index[65]={0x00};
        uchar frame_set_macro_sp_key[65]={0x00};
        uchar frame_set_macro_spkey_index[65]={0x00};
        uchar frame_set_macro[65]={0x00};
        uchar frame_set_mouse[65]={0x00};
        uchar frame_set_media[65]={0x00};
        uchar frame_set_delay[65]={0x00};
        uchar frame_set_delay_index[65]={0x00};

        QVector<uchar> temp_macro_buffer,temp_macro_index_buffer, //macro indecies and buffer
                       temp_macro_sp_buffer,temp_macro_sp_index,  //macro sp indecies and buffer
                       temp_delay_index,temp_delay_buffer;        //macro delay indecies ande buffer

        //initialize vector
        temp_macro_index_buffer.append(0x00);

        //set report ID = 0x00
        frame_set_normal           [0]= 0x00;
        frame_set_sp               [0]= 0x00;
        frame_set_macro_status     [0]= 0x00;
        frame_set_macro_index      [0]= 0x00;
        frame_set_macro_sp_key     [0]= 0x00;
        frame_set_macro_spkey_index[0]= 0x00;
        frame_set_macro            [0]= 0x00;
        frame_set_mouse            [0]= 0x00;
        frame_set_media            [0]= 0x00;
        frame_set_delay            [0]= 0x00;
        frame_set_delay_index      [0]= 0x00;

        //set frame header
        frame_set_normal           [1]= 0x01;   // set KEY_CODE          [10]
        frame_set_sp               [1]= 0x02;   // set SP_KEY_CODE       [10]
        frame_set_macro_status     [1]= 0x03;   // set KEY_marco         [2]
        frame_set_macro_index      [1]= 0x04;   // set marco_SPLIT_INDX  [5]
        frame_set_macro_sp_key     [1]= 0x05;   // set marco_SPE_KEYCODE [10]
        frame_set_macro_spkey_index[1]= 0x06;   // set marco_SPE_KEYINDX [10]
        frame_set_macro            [1]= 0x07;   // set marco_KEYCODE     [40]
        frame_set_mouse            [1]= 0x08;   // set MOUSE_CODE        [10]
        frame_set_media            [1]= 0x09;   // set MEDIA_CODE        [10]
        frame_set_delay            [1]= 0x0a;   // set marco_DELAY       [10]
        frame_set_delay_index      [1]= 0x0b;   // set marco_DELAY_INDX  [10]

        //generate frames
        for(int i = 0;i<this->getKeynum();i++){
            uchar temp_normal = 0x00;   //normal
            uchar temp_sp = 0x00;       //specoal
            uchar temp_mouse = 0x00;    //mouse
            uchar temp_media = 0x00;    //media
            if(!this->getCustomKeyByID(i)->isMacro()){
                //normal key
                table->convertNormaltKeyValue2Hex(&temp_normal,&temp_sp,this->getCustomKeyByID(i)->getKeyValueList()[0]);
                //single key
                temp_mouse = table->getHex(getCustomKeyByID(i)->getKeyValueList()[0]->getMouseKeyIndex());
                temp_media = table->getHex(getCustomKeyByID(i)->getKeyValueList()[0]->getMediaKeyIndex());
            }
            else{
                //set one macro key to temp buffer
                QVector<KeyValue*> tkvs = this->getCustomKeyByID(i)->getKeyValueList();
                for(int x =0;x<tkvs.size();x++){
                    uchar normal = 0x00;
                    uchar special = 0x00;
                    uchar delay = 0x00;
                    table->convertNormaltKeyValue2Hex(&normal,&special,this->getCustomKeyByID(i)->getKeyValueList()[x]);
                    delay = getCustomKeyByID(i)->getKeyValueList()[x]->getDelay();
                    //set normal key buffer
                    temp_macro_buffer.append(normal);
                    //set special key buffer
                    if(special!=0x00){
                        temp_macro_sp_buffer.append(special);
                        temp_macro_sp_index.append((uchar)(temp_macro_buffer.size()-1));
                    }
                    //set delay to key
                    if(delay!=0x00){
                        temp_delay_buffer.append(delay);
                        temp_delay_index.append((uchar)(temp_macro_buffer.size()-1));
                    }
                }
                temp_macro_index_buffer.append((uchar)temp_macro_buffer.size());
            }
            //construct normal key frame
            frame_set_mouse[i+2] = temp_mouse;
            frame_set_media[i+2] = temp_media;
            frame_set_normal[i+2] = temp_normal;
            frame_set_sp[i+2] = temp_sp;
        }
        //construct macro key frames
        //1.frame_set_macro_status
        uchar hi = 0x00;
        uchar lo = 0x00;
        //set low byte
        for(int i=0;i<9;i++){
            if(this->getCustomKeyByID(i)->isMacro()){
                lo|=(0x01<<i);
            }
        }
        //set high byte
        if(this->getKeynum()>8){
            for(int i=8;i<10;i++){
                if(this->getCustomKeyByID(i)->isMacro()){
                    hi|=(0x01<<(i-8));
                }
            }
        }
        //construct frame
        frame_set_macro_status[2] = hi;//set hi
        frame_set_macro_status[3] = lo;//set lo

        //set frame_set_macro_index
        int i = 1;
        for(;i<temp_macro_index_buffer.size();i++){
            frame_set_macro_index[i+2] = temp_macro_index_buffer[i];
        }
        for(;i<this->macro_key_count+1;i++){
            frame_set_macro_index[i+2] = temp_macro_buffer.size();
        }
        //set frame_set_macro_sp_key
        for(int i =0;i<temp_macro_sp_buffer.size();i++){
            frame_set_macro_sp_key[i+2] = temp_macro_sp_buffer[i];
        }

        //set frame_set_macro_spkey_index
        for(int i =0;i<temp_macro_sp_index.size();i++){
            frame_set_macro_spkey_index[i+2] = temp_macro_sp_index[i];
        }

        //set frame_set_delay
        for(int i =0;i<temp_delay_buffer.size();i++){
            frame_set_delay[i+2] = temp_delay_buffer[i];
        }

        //set frame_set_delay_index
        for(int i =0;i<temp_delay_index.size();i++){
            frame_set_delay_index[i+2] = temp_delay_index[i];
        }

        //set frame_set_macro
        for(int i =0;i<temp_macro_buffer.size();i++){
            frame_set_macro[i+2] = temp_macro_buffer[i];
        }


        bool get_ack = false;
        //set hid device to blocking mode
        hid_set_nonblocking(my_device,0);
        //send setting frames to device
        int res1 = hid_write(my_device, frame_set_normal, 65);  // -1 for error
        get_ack = getACK(my_device);
        int res2 = hid_write(my_device, frame_set_sp, 65);      // -1 for error
        get_ack = (getACK(my_device) && get_ack);
        int res3 = hid_write(my_device,frame_set_macro_status,65);
        get_ack = (getACK(my_device) && get_ack);
        int res4 = hid_write(my_device,frame_set_macro_index,65);
        get_ack = (getACK(my_device) && get_ack);
        int res5 = hid_write(my_device,frame_set_macro_sp_key,65);
        get_ack = (getACK(my_device) && get_ack);
        int res6 = hid_write(my_device,frame_set_macro_spkey_index,65);
        get_ack = (getACK(my_device) && get_ack);
        int res8 = hid_write(my_device,frame_set_mouse,65);
        get_ack = (getACK(my_device) && get_ack);
        int res9 = hid_write(my_device,frame_set_media,65);
        get_ack = (getACK(my_device) && get_ack);
        int res10= hid_write(my_device,frame_set_delay,65);
        get_ack = (getACK(my_device) && get_ack);
        int res11= hid_write(my_device,frame_set_delay_index,65);
        get_ack = (getACK(my_device) && get_ack);
        int res7 = hid_write(my_device,frame_set_macro,65);
        get_ack = (getACK(my_device) && get_ack);

        if(res1 != -1 && res2 != -1 && res3!= -1 && res4 != -1 && res5 != -1
                && res6 != -1 && res7 != -1 && res8 != -1 && res9 !=-1 && res10 != -1
                && res11!= -1 )
        {
            if(!get_ack){
                last_error = tr("Can not get all ACKs!");
                qDebug() << "Can not get all ACKs.";
                logToMain("Can not get all ACKs.");
                hid_close(my_device);
                return 0;
            }else{
                qDebug() << "Sending Successfully!";
                logToMain("Sending Successfully!");
                hid_close(my_device);
                return 1;
            }
        }else{
            //wirte failed
            last_error = tr("Data sending is failed!");
            QString text = QString::fromWCharArray(hid_error(my_device));
            qDebug() << "Sending Failed! Error:"<< text;
            logToMain("Data sending is failed!");
            hid_close(my_device);
            return -1;
        }
    }
    else{
        last_error = tr("Can not open device!");
        return -1;
    }
}
bool CustomKeyboard::getACK(hid_device *opened_device)
{
    uchar ACK[64]      = {0x00};
    //read ack
    int read_count =  hid_read_timeout(opened_device,ACK,64,500);
    if(read_count < 0){
        last_error = tr("Can not read ACK frame.");
        logToMain("Can not read ACK frame.");
        return false;
    }else{
        //check ACK
        if(ACK[0]==0x55 && ACK[1] == 0x55 && ACK[2] == 0x55){
            qDebug() << "ACK correct.";
            logToMain("ACK correct.");
            return true;
        }else{
            last_error =tr( "ACK not correct.");
            qDebug() << "ACK NOT correct.";
            logToMain("ACK NOT correct.");
            return false;
        }
    }
}
bool CustomKeyboard::testHardware()
{
    //open device
    hid_device *my_device;
    my_device = hid_open(vid,pid,nullptr);
    bool is_ok = false;
    if(my_device!=NULL){
        qDebug() << "device opened.";
        logToMain("Device is opened.");
        //opened
        uchar test_frame[65]={0x00};
        //init array
        for(int i=0;i<65;i++){
            test_frame[i] = 0x05;
        }
        test_frame[0] = 0x00;
        test_frame[1] = 0x0c;
        int res = hid_write(my_device, test_frame, 65);
        if(res == -1){
            qDebug() << "can not send test framed.";
            logToMain("Can NOT send test framed.");
        }
        else{
            uchar test_receive[128] = {0x00};
            uchar test_receive2[128] = {0x00};
            qDebug() << "send test framed ok.";
            logToMain("send test framed ok.");
            int read_count =  hid_read(my_device,test_receive,128);
            int read_count2 =  hid_read_timeout(my_device,test_receive2,128,1000);
            if(read_count == -1 || read_count2 == -1){
                 qDebug() << "can not read.";
                 logToMain("Can NOT read");
                 //failed
            }
            else{
                qDebug() << "read from device. read_count =" << read_count;
                logToMain("read from device. read_count ="+ QString::number(read_count));
                QString tempstr = "";
                for(int i =0 ;i<read_count;i++){
                    tempstr += QString::number((int)test_receive[i])+ " ";
                }
                qDebug() << "test_receive = "+tempstr;
                logToMain("test_receive = "+tempstr);

                qDebug() << "read from device. read_count2 =" << read_count2;
                logToMain("read from device. read_count2 ="+QString::number(read_count2));
                QString tempstr2 = "";
                for(int i =0 ;i<read_count2;i++){
                    tempstr2 += QString::number((int)test_receive2[i])+ " ";
                }
                qDebug() << "test_receive2 = "+tempstr2;
                logToMain("test_receive2 = "+tempstr2);
                is_ok = true;
            }
        }

    }
    else{
        qDebug() << "can not open device.";
        logToMain("Can Not open device.");
        return false;
    }
    hid_close(my_device);
    return is_ok;
}

bool CustomKeyboard::tryOpen()
{
    //open device
    hid_device *my_device;
    my_device = hid_open(vid,pid,nullptr);
    bool success = true;
    if(my_device==NULL)
        success = false;
    hid_close(my_device);
    return success;
}
/****************************
 *   Get Firmware Veriosn
 *
 * @return:  0 -> old firmware
 *           1 -> new firmware
 *          -1 -> error
 *
****************************/
int CustomKeyboard::getVersion()
{
    //open device
    hid_device *my_device;
    int ret = 0;
    my_device = hid_open(vid,pid,nullptr);
    if(my_device!=nullptr){
        uchar test_frame[65]={0x00};
        test_frame[0] = 0x00;
        test_frame[1] = 0x0d;
        //send get-version frame
        int res = hid_write(my_device, test_frame, 65);
        logToMain("getting version...");
        if(res == -1){
            logToMain("Can not wirte to device:-2.");
            ret =  -2;//can not write to deive
        }
        else{
            uchar VER[128] = {0x00};
            int read_count =  hid_read_timeout(my_device,VER,128,500);
            if(read_count>0){
                if(VER[0] == 0x00){
                    logToMain("device version = 0.");
                }else if(VER[0] == 0x01){
                    logToMain("device version is new:1.");
                    ret = 1;
                }else{
                    logToMain("device version = 0:old.");
                }
            }else{
                logToMain("Can not receive VERSION frame:-3.");
                logToMain("Firmware version is out of date.");
            }
        }
        hid_close(my_device);
        return ret;
    }
    else{
        logToMain("Can not open device:-1.");
        return -1; //can not open device
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
int CustomKeyboard::getMacroMem(){
    return this->macro_mem;
}
int CustomKeyboard:: getMacroSPkeyMem(){
    return this->macro_spkey;
}
CustomKey* CustomKeyboard::getCustomKeyByID(int key_no){
    return this->key_list[key_no];
};
CustomKeyboard::~CustomKeyboard(){
    delete this->normal_keycode;
    delete this->spkey_mixcode;
    qDeleteAll(this->key_list);
}

QJsonObject CustomKeyboard::toJsonObj()
{
    QJsonObject ckbjson = QJsonObject();
    ckbjson.insert("name",this->name);
    ckbjson.insert("pid",this->pid);
    ckbjson.insert("vid",this->vid);
    ckbjson.insert("keynum",this->keynum);
    QJsonArray cklist = QJsonArray();
    for(int i = 0;i<this->key_list.size();i++){
        cklist.append(this->key_list[i]->toJsonObj());
    }
    ckbjson.insert("ck_list",cklist);
    return ckbjson;
}

CustomKeyboard *CustomKeyboard::fromJson(QJsonObject jsonobj, QPushButton *(*mapping_button_list))
{
    QString _name = jsonobj.value("name").toString();
    unsigned short _pid = (unsigned short)jsonobj.value("pid").toInt();
    unsigned short _vid = (unsigned short)jsonobj.value("vid").toInt();
    int _keynum = jsonobj.value("keynum").toInt();
    QJsonArray jsonarray = jsonobj.value("ck_list").toArray();
    QVector<CustomKey*> *ck_list = new QVector<CustomKey*>();
    for(int i = 0;i<_keynum;i++){
        QJsonValue qjv = jsonarray[i];
        CustomKey *ck = CustomKey::fromJson(qjv.toObject(),mapping_button_list[i]);
        ck_list->append(ck);
    }
    CustomKeyboard *ckb = new CustomKeyboard(_name,_keynum,_pid,_vid,mapping_button_list);
    ckb->setKeyList(*ck_list);
    return ckb;
}

int CustomKeyboard::getMacro_mem() const
{
    return macro_mem;
}

int CustomKeyboard::getMacro_spkey() const
{
    return macro_spkey;
}

int CustomKeyboard::getMacro_delay() const
{
    return macro_delay;
}

int CustomKeyboard::getMacro_key_count() const
{
    return macro_key_count;
}





