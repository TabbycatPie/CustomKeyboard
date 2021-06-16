#ifndef CONGIFSAVER_H
#define CONGIFSAVER_H

#include <QObject>

class ConfigSaver : public QObject
{
    Q_OBJECT
public:
    explicit ConfigSaver(QObject *parent = nullptr);
    bool saveConfig(QString filename,QJsonObject obj);
    bool readConfig(QString filename,QJsonObject* obj);
    QString getLastError();
private:
    QString default_path;
    QString last_error;


signals:

};

#endif // CONGIFSAVER_H
