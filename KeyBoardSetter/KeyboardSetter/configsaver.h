#ifndef CONGIFSAVER_H
#define CONGIFSAVER_H

#include <QObject>

class ConfigSaver : public QObject
{
    Q_OBJECT
public:
    explicit ConfigSaver(QObject *parent = nullptr);
    bool saveConfig(QString name,QJsonObject obj);
    bool readConfig(QString name,QJsonObject* obj);
    QString getLastError();
private:
    QString default_path;
    QString last_error;


signals:

};

#endif // CONGIFSAVER_H
