#include "configsaver.h"
#include "QFile"

#include <QDataStream>
#include <QJsonDocument>
#include <QJsonObject>


ConfigSaver::ConfigSaver(QObject *parent)
{
    this->default_path = "";
    this->last_error = "";
}

bool ConfigSaver::saveConfig(QString filename, QJsonObject obj)
{
    //open file
    QFile file(filename);
    //open file failed
    if (!(file.open(QIODevice::ReadWrite))){
        last_error = tr("Can not open file.");
        return false;
    }

    //write object to file
    QJsonDocument jsonDoc;
    jsonDoc.setObject(obj);
    file.write(jsonDoc.toJson());
    file.close();
    return true;
}

bool ConfigSaver::readConfig(QString filename, QJsonObject *obj)
{
    QFile file(filename);
    //open file failed
    if (!(file.open(QIODevice::ReadOnly))){
        last_error = tr("Can not open file.");
        return false;
    }
    //write object to file
    QJsonParseError jsonerror;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll(),&jsonerror);
    if (!jsonDoc.isNull() && (jsonerror.error == QJsonParseError::NoError)){
        //json parse success
        *obj = jsonDoc.object();
    }
    else{
        //json parse error
        last_error = tr("Json parse error,File is broken!");
        return false;
    }

    return true;
}

QString ConfigSaver::getLastError()
{
    return last_error;
}
