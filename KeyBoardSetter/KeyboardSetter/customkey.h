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
    CustomKey(QString _name,QPushButton *mapping_key,bool _is_macro);
    //getter and setter
    void setMacro(bool is_macro);
    QPushButton *getMappingButton();
    QString getName();
    void setName(QString _name);
    bool isMacro();
    bool isMouse();
    bool isMedia();

    //edit key
    void setKey(QVector<KeyValue*> _keys);
    void setKey(KeyValue* _key);
    void appendKey(KeyValue* _key);
    bool deleteTopKey();//@return false : key list is empty

    //info
    int getKeyValueCount();//return the total count of keyvalues in the kv_list
    QVector<KeyValue*> getKeyValueList();

    //tojson
    QJsonObject toJsonObj();

    ~CustomKey();
private:
    QVector<KeyValue*> keys;
    QPushButton *mapping_btn;
    QString name;
    bool is_macro;
    bool is_mouse;
    bool is_media;
    //int normalkey_index;
signals:

};

#endif // CUSTOMKEY_H
