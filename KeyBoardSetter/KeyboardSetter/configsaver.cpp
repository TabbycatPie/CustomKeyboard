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

QString ConfigSaver::getLastError()
{
    return last_error;
}
