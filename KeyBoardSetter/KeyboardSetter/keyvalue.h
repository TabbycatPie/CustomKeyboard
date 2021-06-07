#ifndef KEYVALUE_H
#define KEYVALUE_H

#include <QObject>
#include <QVector>
#include <qjsonobject.h>

class KeyValue : public QObject
{
    Q_OBJECT
public:
    KeyValue(int _normalkey,int _mousekey,int meidakey,QVector<int> spkeys);
    KeyValue(int _normalkey);
    void setValue(int _normalkey,int _mousekey,int meidakey,QVector<int> spkeys);
    int getNormalKeyIndex();
    int getMouseKeyIndex();
    int getMediaKeyIndex();
    uchar getDelay();
    void setDelay(uchar _delay);
    QVector<int> getSPKeyList();
    QJsonObject toJsonObj();
    ~KeyValue();
private:
    int normalkey;
    int mousekey;
    int mediakey;
    uchar delay;
    QVector<int> sp_keys;
signals:

};

#endif // KEYVALUE_H
