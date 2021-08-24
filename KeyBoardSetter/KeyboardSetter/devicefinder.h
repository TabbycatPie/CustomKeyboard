#ifndef DEVICEFINDER_H
#define DEVICEFINDER_H


#include "mainwindow.h"
#include <QMainWindow>

namespace Ui {
class DeviceFinder;
}

class DeviceFinder : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeviceFinder(QWidget *parent = nullptr);

    ~DeviceFinder();
    void setMw(MainWindow* mainwindow);

private:
    Ui::DeviceFinder *ui;
    MainWindow*  mw;
    void changeLanguage(QString language);
    void openMainWindow();
};

#endif // DEVICEFINDER_H
