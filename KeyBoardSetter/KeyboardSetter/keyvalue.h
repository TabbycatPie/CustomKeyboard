#ifndef KEYVALUE_H
#define KEYVALUE_H

#include <QObject>
#include <QVector>

class KeyValue : public QObject
{
    Q_OBJECT
public:
    KeyValue(int _normalkey,QVector<int> spkeys);
    KeyValue(int _normalkey);
    void setValue(int _normalkey,QVector<int> spkeys);
    int getNormalKeyIndex();
    QVector<int> getSPKeyList();
    ~KeyValue();
private:
    int normalkey;
    QVector<int> sp_keys;
signals:

};

#endif // KEYVALUE_H
