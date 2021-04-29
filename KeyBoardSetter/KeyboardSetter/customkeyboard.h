#ifndef CUSTOMKEYBOARD_H
#define CUSTOMKEYBOARD_H

#include <QObject>

class CustomKeyboard : public QObject
{
    Q_OBJECT
public:
    CustomKeyboard(int keynum,uint16_t pid,uint16_t vid,int marco_mem,int marco_spkey_mem);
    //getter and setter
    uint16_t getPid();
    uint16_t getVid();
    int getKeynum();
    int getMarcoMem();
    int getMarcoSPkeyMem();
    void setNormalKey(int setkey_no,uchar keytable_no,uchar spkeytable_no);
    ~CustomKeyboard();
private:
    uint16_t pid;       //production id
    uint16_t vid;       //vender     id
    int keynum;         //how many keys your device have
    int marco_mem;      //max number of marco_key memory on device
    int marco_spkey;    //max number of marco special key memort on device
    uchar *normal_keycode;  //normal key code
    uchar *spkey_mixcode;   //special key mix code

signals:

};

#endif // CUSTOMKEYBOARD_H
