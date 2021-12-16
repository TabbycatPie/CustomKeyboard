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
    dw.show();

    return a.exec();
}
