#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qtranslator.h>
#include "customkeyboard.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    bool isSpecialKey(int index);
    void updateUI();
    void commitKeySetting();
    void initTreeView();
    bool downloadToDevice(int keyboard_no);
    bool addKeyValue();
    bool deleteKeyValue();
    //functions of delay
    void delayindecrease(bool is_add=true);
    void setDelay();
    bool saveConfigToFile();
    CustomKeyboard* loadConfigFromFile();
    void initData(QTranslator *translator);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //Translator
    QTranslator *translator =NULL;


private slots:
    void softKeyPressed(int i);   //button on keyboard pressed
    void setKeyPress(int key_no);
    void setKeyRelease();
    void setKey(int key_no);      //open softkey board window
    void switchKeyboard(int keyboard_no);
    void changeLanguage(QString language);
    void logUpdate(QString text);
};
#endif // MAINWINDOW_H
