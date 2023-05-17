#ifndef HIDCODETABLE_H
#define HIDCODETABLE_H

#include "Utils/keyvalue.h"
#include <QObject>
#include <QVector>

class HIDCodeTable : public QObject
{
    Q_OBJECT
public:
    HIDCodeTable();
    bool isSPkey(int key_no);
    bool isMouseKey(int key_no);
    bool isMediaKey(int key_no);
    QString getKeyString(int key_no);
    QString getButtonNmae(int key_no);
    uchar getHex(int key_no);
    uchar getSpKeyHex(QVector<int> spkey_list);
    void convertNormaltKeyValue2Hex(uchar * normal,uchar * sp_key,KeyValue *kv);
    KeyValue* convertVector2KeyValue(int normal,int mouse,int media,const QVector<int> sp_keys);
    QString convertKeyValue2QString(KeyValue *kv);
    int getSPkeybByindex(int x);
    ~HIDCodeTable();

private:
    const QString *key_string;
    const QString *key_name;
    const uchar *key_hex;
    const int *spkey_index;
    const int *mouse_index;
    const int *media_index;
signals:

};

#endif // HIDCODETABLE_H
