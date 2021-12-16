#ifndef DEVICEFINDER_H
#define DEVICEFINDER_H


#include <QMainWindow>
#include <configform.h>

namespace Ui {
class DeviceFinder;
}

class DeviceFinder : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeviceFinder(QWidget *parent = nullptr);

    ~DeviceFinder();
    void setMw(ConfigForm* mainwindow);

private:
    Ui::DeviceFinder *ui;
    ConfigForm*  mw;
    void changeLanguage(QString language);
    void openMainWindow();
};

#endif // DEVICEFINDER_H
