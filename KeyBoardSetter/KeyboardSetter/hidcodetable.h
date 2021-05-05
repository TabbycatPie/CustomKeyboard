#ifndef HIDCODETABLE_H
#define HIDCODETABLE_H

#include "keyvalue.h"
#include <QObject>
#include <QVector>

class HIDCodeTable : public QObject
{
    Q_OBJECT
public:
    HIDCodeTable();
    bool isSPkey(int key_no);
    QString getKeyString(int key_no);
    uchar getHex(int key_no);
    uchar getSpKeyHex(QVector<int> spkey_list);
    void convertNormaltKeyValue2Hex(uchar * normal,uchar * sp_key,KeyValue *kv);
    KeyValue* convertVector2KeyValue(int normal,const QVector<int> sp_keys);
    QString convertKeyValue2QString(KeyValue *kv);
    ~HIDCodeTable();
private:
    const QString *key_string;
    const uchar *key_hex;
    const int *spkey_index;
signals:

};

#endif // HIDCODETABLE_H
