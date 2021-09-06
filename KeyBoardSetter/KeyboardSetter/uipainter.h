#ifndef UIPAINTER_H
#define UIPAINTER_H

#include <QObject>
#include <qpushbutton.h>

class UIPainter : public QObject
{
    Q_OBJECT
public:
    explicit UIPainter(QWidget* ui,QObject *parent = nullptr);
    void drawCKB(int x, int y, int col, int row);
    void drawVKBmain(int x, int y);
    int getCKBWigth(int col);
    int getCKBHeight(int row);

    //------getter and setter
    void setCKBKey_len(int value);
    void setCKBKey_inter_margin(int value);
    void setCKBKey_ex_margin(int value);
    void setVKey_len(int value);
    void setVkey_inter_margin(int value);


private:
    QWidget *my_ui;
    int CKBKey_len = 90;
    int CKBKey_inter_margin = 2;
    int CKBKey_ex_margin = 10;
    int VKey_len = 40;
    int Vkey_inter_margin = 2;

    void drawCKBbase(int x, int y, int col, int row);
    QPushButton *drawCKBkey(int x, int y, QString text);
    QPushButton *drawVKey(int x, int y, float block, QString text);
signals:

};

#endif // UIPAINTER_H
