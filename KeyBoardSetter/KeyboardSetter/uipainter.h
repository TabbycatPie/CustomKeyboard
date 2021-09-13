#ifndef UIPAINTER_H
#define UIPAINTER_H

#include <QObject>
#include <qpushbutton.h>
#include <QVector>
#include <qlabel.h>

class UIPainter : public QObject
{
    Q_OBJECT
public:
    explicit UIPainter(QWidget* ui,QObject *parent = nullptr);

    enum VinputEnable{VKEYBOARD,VMOUSE,VADVANCE};
    //draw custom keyboard
    void drawCKB(int x, int y, int col, int row);
    int getCKBWigth(int col);
    int getCKBHeight(int row);
    //draw Virtual keyboard
    void drawVKBmain(int x, int y);
    void drawVKBfunc(int x, int y);
    void drawVKBkeypad(int x, int y);
    void drawVKBfull(int x, int y);
    void hideVKB();
    void showVKB();
    //draw virtaul mouse
    void drawVMouse(int x,int y);
    void showVMouse();
    void hideVMouse();
    //draw switch
    void switchVinput(VinputEnable);
    void drawSwitch(int x, int y) const;
    void triggerSwitch(int btn_no);

    int getFullWindowHeight(int CKBrow);
    int getFullWindowWidth();

    //------getter and setter
    void setCKBKey_len(int value);
    void setCKBKey_inter_margin(int value);
    void setCKBKey_ex_margin(int value);
    void setVKey_len(int value);
    void setVkey_inter_margin(int value);
    void setUI_part_margin(int value);
    int  getUI_part_margin() const;

    QVector<QPushButton *> *getVkey_list() const;
    QVector<QPushButton *> *getCKBkey_list() const;
    QVector<QPushButton *> *getSW_list() const;

private:
    QWidget *my_ui;
    int CKBKey_len = 90;
    int CKBKey_inter_margin = 2;
    int CKBKey_ex_margin = 10;
    int VKey_len = 40;
    int Vkey_inter_margin = 2;
    int UI_part_margin = 20;

    void drawCKBbase(int x, int y, int col, int row);

    QPushButton*drawCKBkey(int x, int y, QString text);
    QPushButton* drawVKey(int x,int y,float block_x,float block_y,QString text);

    //----Qpushbutton list
    QVector<QPushButton*> *Vkey_list;
    QVector<QPushButton*> *CKBkey_list;
    QVector<QPushButton*> *SW_list;

    //----other component
    QLabel *mouse_body;

signals:

};

#endif // UIPAINTER_H
