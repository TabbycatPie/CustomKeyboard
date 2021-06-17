#include "userconfig.h"

#include <qjsonobject.h>

UserConfig::UserConfig(QString _language, QObject *parent)
{
    this->language = _language;
}

QString UserConfig::getLanguage() const
{
    return language;
}

void UserConfig::setLanguage(const QString &value)
{
    language = value;
}

QJsonObject UserConfig::toJsonObj()
{
    QJsonObject temp = QJsonObject();
    //generate json
    temp.insert("user_language",this->language);
    return temp;
}

UserConfig *UserConfig::fromJson(QJsonObject jsonobj)
{
    UserConfig *new_config = new UserConfig(jsonobj.value("user_language").toString());
    return new_config;
}
