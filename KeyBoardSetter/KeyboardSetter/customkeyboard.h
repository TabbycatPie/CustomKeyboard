#ifndef CUSTOMKEYBOARD_H
#define CUSTOMKEYBOARD_H

#include "customkey.h"
#include <QObject>
#include <QPushButton>
#include <QVector>

class CustomKeyboard : public QObject
{
    Q_OBJECT
public:
    //contructor
    CustomKeyboard(QString _name,int keynum,uint16_t pid,uint16_t vid,int marco_mem,int marco_spkey_mem,QPushButton *(*_btn_list));
    //getter and setter
    uint16_t getPid();
    uint16_t getVid();
    int getKeynum();
    int getMarcoMem();
    int getMarcoSPkeyMem();
    QPushButton *getButtonByID(int key_no);
    QString getName();

    //set key
    void setKey(int key_id,KeyValue kv);  //normal single
    void setKey(int key_id,QVector<KeyValue*> kvs); //marco
    //download to device
    bool download();
    ~CustomKeyboard();
private:
    QVector<CustomKey*> key_list;//soft-keyboard mapping
    uint16_t pid;       //production id
    uint16_t vid;       //vender     id
    int keynum;         //how many keys your device have
    int marco_mem;      //max number of marco_key memory on device
    int marco_spkey;    //max number of marco special key memort on device
    uchar *normal_keycode;  //normal key code
    uchar *spkey_mixcode;   //special key mix code
    QString name;           //keyboard Name

signals:

};

#endif // CUSTOMKEYBOARD_H
