#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <iostream>

using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //load window
    MainWindow w;
    w.show();
    return a.exec();
}
