#ifndef HIDCODETABLE_H
#define HIDCODETABLE_H

#include <QObject>

class HIDCodeTable : public QObject
{
    Q_OBJECT
public:
    explicit HIDCodeTable(QObject *parent = nullptr);

signals:

};

#endif // HIDCODETABLE_H
