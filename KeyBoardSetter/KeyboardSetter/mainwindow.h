#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void softKeyPressed(int i);   //button on keyboard pressed
    void setKeyPress(int key_no);
    void setKeyRelease();
    void setKey(int key_no);      //open softkey board window
    void switchKeyboard(int keyboard_no);
};
#endif // MAINWINDOW_H
