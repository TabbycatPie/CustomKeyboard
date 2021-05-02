#ifndef CUSTOMKEY_H
#define CUSTOMKEY_H

#include "keyvalue.h"

#include <QObject>
#include <QPushButton>
#include <QVector>

class CustomKey : public QObject
{
    Q_OBJECT
public:
    CustomKey(QString _name,QPushButton *mapping_key,bool _is_marco);
    //getter and setter
    void setMarco(bool is_marco);
    QPushButton *getMappingButton();
    QString getName();
    QVector<KeyValue*> getKeyValueList();
    void setName(QString _name);

    void setKey(QVector<KeyValue*> _keys);
    void setKey(KeyValue* _key);

    bool isMarco();
    ~CustomKey();
private:
    QVector<KeyValue*> keys;
    QPushButton *mapping_btn;
    QString name;
    bool is_marco;
    int normalkey_index;
signals:

};

#endif // CUSTOMKEY_H
