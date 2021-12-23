#ifndef CUSTOMKEYBOARD_H
#define CUSTOMKEYBOARD_H

#include "hidapi.h"
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
    CustomKeyboard(QString _name,int keynum,unsigned short pid,unsigned short vid,QPushButton *(*_btn_list));
    CustomKeyboard(QString _name,int keynum,unsigned short pid,unsigned short vid,QVector<QPushButton*> *btn_list);
    CustomKeyboard(unsigned short pid, unsigned short vid);
    //getter and setter
    void setMacroConfig(int mlen,int mcount,int mspkey,int mdelay);
    unsigned short getPid();
    unsigned short getVid();
    int getKeynum();
    int getMacroMem();
    int getMacroSPkeyMem();
    int getMacro_mem() const;
    int getMacro_spkey() const;
    int getMacro_delay() const;
    int getMacro_key_count() const;
    QPushButton *getButtonByID(int key_no);
    CustomKey *getCustomKeyByID(int key_no);
    QString getName();

    //set key
    void setKey(int key_id,KeyValue *kv);  //normal single
    void setKey(int key_id,QVector<KeyValue*> kvs); //macro
    void appendKey(int key_id,KeyValue *kv);
    void setKeyList(QVector<CustomKey*> list);
    bool deleteTopKey(int key_id);
    bool checkMacroAddable(int cur_key_no);
    //download to device
    int download(HIDCodeTable *table);
    //test
    bool testHardware();
    bool tryOpen();
    int getVersion();


    QString getLastError();
    ~CustomKeyboard();

    //tojson
    QJsonObject toJsonObj();
    static CustomKeyboard *fromJson(QJsonObject jsonobj,QPushButton* (*mapping_button_list));

private:
    QVector<CustomKey*> key_list;//soft-keyboard mapping
    unsigned short pid;       //production id
    unsigned short vid;       //vender     id
    int keynum;         //how many keys your device have
    int macro_mem;      //max number of macro_key memory on device            default is 34
    int macro_spkey;    //max number of macro special key on device           default is 10
    int macro_delay;    //max number of macro delay key on device             default is 10
    int macro_key_count;//max number of macro key on device                   default is 10
    uchar *normal_keycode;  //normal key code
    uchar *spkey_mixcode;   //special key mix code
    QString name;           //keyboard Name
    QString last_error;
    bool getACK(hid_device *opened_device);

signals:
    void logToMain(QString text);
};

#endif // CUSTOMKEYBOARD_H
