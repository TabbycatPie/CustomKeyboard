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
    CustomKeyboard(QString _name,int keynum,unsigned short pid,unsigned short vid,int macro_mem,int macro_spkey_mem,QPushButton *(*_btn_list));
    //getter and setter
    unsigned short getPid();
    unsigned short getVid();
    int getKeynum();
    int getMacroMem();
    int getMacroSPkeyMem();
    QPushButton *getButtonByID(int key_no);
    CustomKey *getCustomKeyByID(int key_no);
    QString getName();

    //set key
    void setKey(int key_id,KeyValue *kv);  //normal single
    void setKey(int key_id,QVector<KeyValue*> kvs); //macro
    void appendKey(int key_id,KeyValue *kv);
    bool deleteTopKey(int key_id);
    bool checkMacroAddable(int cur_key_no);
    //download to device
    bool download(HIDCodeTable *table);
    QString getLastError();
    ~CustomKeyboard();
private:
    QVector<CustomKey*> key_list;//soft-keyboard mapping
    unsigned short pid;       //production id
    unsigned short vid;       //vender     id
    int keynum;         //how many keys your device have
    int macro_mem;      //max number of macro_key memory on device
    int macro_spkey;    //max number of macro special key memort on device
    uchar *normal_keycode;  //normal key code
    uchar *spkey_mixcode;   //special key mix code
    QString name;           //keyboard Name
    QString last_error;

signals:

};

#endif // CUSTOMKEYBOARD_H
