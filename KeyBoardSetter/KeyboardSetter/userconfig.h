#ifndef USERCONFIG_H
#define USERCONFIG_H

#include <QObject>

class UserConfig : public QObject
{
    Q_OBJECT
public:
    explicit UserConfig(QString language,QObject *parent = nullptr);
    QString getLanguage() const;
    void setLanguage(const QString &value);

    //json conversion
    QJsonObject toJsonObj();
    static UserConfig *fromJson(QJsonObject jsonobj);

private:
    QString language;

signals:

};

#endif // USERCONFIG_H
