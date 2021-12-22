#include "configform.h"
#include "devicefinder.h"

#include <QApplication>
#include <QTranslator>
#include <iostream>

using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //load window

    DeviceFinder dw;
    ConfigForm w;

    dw.setMw(&w);
    //load main window when device is pluged in
    //justify wether the device is pluged in
    QPushButton *(*empty);
    if(CustomKeyboard("tryopen",0,0x2019,0x5131,empty).tryOpen())
        w.show();
    else
        dw.show();
    delete empty;

    return a.exec();
}
