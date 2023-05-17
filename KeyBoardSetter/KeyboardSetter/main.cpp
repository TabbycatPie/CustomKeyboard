#include "Forms/configform.h"
#include "Forms/devicefinder.h"

#include <QApplication>
#include <QTranslator>
#include <iostream>

using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //load window

    DeviceFinder dw;
    dw.smartShow();

    return a.exec();
}
