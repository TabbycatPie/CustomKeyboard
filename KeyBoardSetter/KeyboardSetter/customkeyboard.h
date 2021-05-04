#ifndef CUSTOMKEYBOARD_H
#define CUSTOMKEYBOARD_H

#include "hidcodetable.h"
#include "customkey.h"
#include <QObject>
#include <QPushButton>
#include <QVector>

class CustomKeyboard : public QObject
{
    Q_OBJECT
public:
    //contructor
    CustomKeyboard(QString _name,int keynum,unsigned short pid,unsigned short vid,int marco_mem,int marco_spkey_mem,QPushButton *(*_btn_list));
    //getter and setter
    unsigned short getPid();
    unsigned short getVid();
    int getKeynum();
    int getMarcoMem();
    int getMarcoSPkeyMem();
    QPushButton *getButtonByID(int key_no);
    CustomKey *getCustomKeyByID(int key_no);
    QString getName();

    //set key
    void setKey(int key_id,KeyValue *kv);  //normal single
    void setKey(int key_id,QVector<KeyValue*> kvs); //marco
    //download to device
    bool download(HIDCodeTable *table);
    QString getLastError();
    ~CustomKeyboard();
private:
    QVector<CustomKey*> key_list;//soft-keyboard mapping
    unsigned short pid;       //production id
    unsigned short vid;       //vender     id
    int keynum;         //how many keys your device have
    int marco_mem;      //max number of marco_key memory on device
    int marco_spkey;    //max number of marco special key memort on device
    uchar *normal_keycode;  //normal key code
    uchar *spkey_mixcode;   //special key mix code
    QString name;           //keyboard Name
    QString last_error;

signals:

};

#endif // CUSTOMKEYBOARD_H
