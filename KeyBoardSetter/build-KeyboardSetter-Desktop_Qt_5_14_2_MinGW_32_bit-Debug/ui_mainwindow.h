/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionOpen_Device;
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *btn_testkey1;
    QPushButton *btn_testkey2;
    QPushButton *btn_testkey1_2;
    QPushButton *btn_testkey2_2;
    QPushButton *btn_testkey2_3;
    QWidget *tab_2;
    QPushButton *btn_setcancel_2;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;
    QDockWidget *dockKeyboard;
    QWidget *dockWidgetContents;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *btn_wave;
    QToolButton *btn_1;
    QToolButton *btn_2;
    QToolButton *btn_3;
    QToolButton *btn_4;
    QToolButton *btn_5;
    QToolButton *btn_6;
    QToolButton *btn_7;
    QToolButton *btn_8;
    QToolButton *btn_9;
    QToolButton *btn_0;
    QToolButton *btn_minus;
    QToolButton *btn_add;
    QToolButton *btn_backspace;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *btn_tab;
    QToolButton *btn_q;
    QToolButton *btn_w;
    QToolButton *btn_e;
    QToolButton *btn_r;
    QToolButton *btn_t;
    QToolButton *btn_y;
    QToolButton *btn_u;
    QToolButton *btn_i;
    QToolButton *btn_o;
    QToolButton *btn_p;
    QToolButton *btn_leftbracket;
    QToolButton *btn_rightbracket;
    QToolButton *btn_splash;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *btn_caps;
    QToolButton *btn_a;
    QToolButton *btn_s;
    QToolButton *btn_d;
    QToolButton *btn_f;
    QToolButton *btn_g;
    QToolButton *btn_h;
    QToolButton *btn_j;
    QToolButton *btn_k;
    QToolButton *btn_l;
    QToolButton *btn_split;
    QToolButton *btn_quote;
    QToolButton *btn_enter;
    QWidget *layoutWidget_4;
    QHBoxLayout *horizontalLayout_5;
    QToolButton *btn_lshift;
    QToolButton *btn_z;
    QToolButton *btn_x;
    QToolButton *btn_c;
    QToolButton *btn_v;
    QToolButton *btn_b;
    QToolButton *btn_n;
    QToolButton *btn_m;
    QToolButton *btn_lessthan;
    QToolButton *btn_greaterthan;
    QToolButton *btn_quest;
    QToolButton *btn_rshift;
    QWidget *layoutWidget_5;
    QHBoxLayout *horizontalLayout_6;
    QToolButton *btn_lctrl;
    QToolButton *btn_lwin;
    QToolButton *btn_lalt;
    QToolButton *btn_space;
    QToolButton *btn_ralt;
    QToolButton *btn_rwin;
    QToolButton *btn_rctrl;
    QWidget *layoutWidget_6;
    QHBoxLayout *horizontalLayout_8;
    QToolButton *btn_left;
    QToolButton *btn_down;
    QToolButton *btn_right;
    QToolButton *btn_up;
    QLabel *tvkey_out;
    QPushButton *btn_setcommit;
    QPushButton *btn_setcancel;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QToolButton *btn_esc;
    QToolButton *btn_f1;
    QToolButton *btn_f2;
    QToolButton *btn_f3;
    QToolButton *btn_f4;
    QToolButton *btn_f5;
    QToolButton *btn_f6;
    QToolButton *btn_f7;
    QToolButton *btn_f8;
    QToolButton *btn_f9;
    QToolButton *btn_f10;
    QToolButton *btn_f11;
    QToolButton *btn_f12;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_7;
    QToolButton *btn_ptsr;
    QToolButton *btn_del;
    QToolButton *btn_ins;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(900, 736);
        MainWindow->setMinimumSize(QSize(900, 600));
        MainWindow->setMaximumSize(QSize(900, 16777215));
        MainWindow->setAnimated(true);
        MainWindow->setDockOptions(QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks|QMainWindow::ForceTabbedDocks);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionOpen_Device = new QAction(MainWindow);
        actionOpen_Device->setObjectName(QString::fromUtf8("actionOpen_Device"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(3, 1, 751, 431));
        tabWidget->setMinimumSize(QSize(0, 0));
        tabWidget->setMaximumSize(QSize(900, 900));
        tabWidget->setUsesScrollButtons(true);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        widget = new QWidget(tab);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(30, 30, 481, 92));
        horizontalLayout_9 = new QHBoxLayout(widget);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        btn_testkey1 = new QPushButton(widget);
        btn_testkey1->setObjectName(QString::fromUtf8("btn_testkey1"));
        btn_testkey1->setMinimumSize(QSize(90, 90));

        horizontalLayout_9->addWidget(btn_testkey1);

        btn_testkey2 = new QPushButton(widget);
        btn_testkey2->setObjectName(QString::fromUtf8("btn_testkey2"));
        btn_testkey2->setMinimumSize(QSize(90, 90));

        horizontalLayout_9->addWidget(btn_testkey2);

        btn_testkey1_2 = new QPushButton(widget);
        btn_testkey1_2->setObjectName(QString::fromUtf8("btn_testkey1_2"));
        btn_testkey1_2->setMinimumSize(QSize(90, 90));

        horizontalLayout_9->addWidget(btn_testkey1_2);

        btn_testkey2_2 = new QPushButton(widget);
        btn_testkey2_2->setObjectName(QString::fromUtf8("btn_testkey2_2"));
        btn_testkey2_2->setMinimumSize(QSize(90, 90));

        horizontalLayout_9->addWidget(btn_testkey2_2);

        btn_testkey2_3 = new QPushButton(widget);
        btn_testkey2_3->setObjectName(QString::fromUtf8("btn_testkey2_3"));
        btn_testkey2_3->setMinimumSize(QSize(90, 90));

        horizontalLayout_9->addWidget(btn_testkey2_3);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());
        btn_setcancel_2 = new QPushButton(centralwidget);
        btn_setcancel_2->setObjectName(QString::fromUtf8("btn_setcancel_2"));
        btn_setcancel_2->setGeometry(QRect(780, 70, 91, 30));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 900, 30));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        dockKeyboard = new QDockWidget(MainWindow);
        dockKeyboard->setObjectName(QString::fromUtf8("dockKeyboard"));
        dockKeyboard->setMinimumSize(QSize(900, 242));
        dockKeyboard->setMaximumSize(QSize(900, 242));
        dockKeyboard->setAutoFillBackground(true);
        dockKeyboard->setFloating(false);
        dockKeyboard->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dockKeyboard->setAllowedAreas(Qt::BottomDockWidgetArea);
        dockKeyboard->setWindowTitle(QString::fromUtf8(""));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        layoutWidget = new QWidget(dockWidgetContents);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(51, 60, 531, 30));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        btn_wave = new QToolButton(layoutWidget);
        btn_wave->setObjectName(QString::fromUtf8("btn_wave"));

        horizontalLayout_2->addWidget(btn_wave);

        btn_1 = new QToolButton(layoutWidget);
        btn_1->setObjectName(QString::fromUtf8("btn_1"));

        horizontalLayout_2->addWidget(btn_1);

        btn_2 = new QToolButton(layoutWidget);
        btn_2->setObjectName(QString::fromUtf8("btn_2"));

        horizontalLayout_2->addWidget(btn_2);

        btn_3 = new QToolButton(layoutWidget);
        btn_3->setObjectName(QString::fromUtf8("btn_3"));

        horizontalLayout_2->addWidget(btn_3);

        btn_4 = new QToolButton(layoutWidget);
        btn_4->setObjectName(QString::fromUtf8("btn_4"));

        horizontalLayout_2->addWidget(btn_4);

        btn_5 = new QToolButton(layoutWidget);
        btn_5->setObjectName(QString::fromUtf8("btn_5"));

        horizontalLayout_2->addWidget(btn_5);

        btn_6 = new QToolButton(layoutWidget);
        btn_6->setObjectName(QString::fromUtf8("btn_6"));

        horizontalLayout_2->addWidget(btn_6);

        btn_7 = new QToolButton(layoutWidget);
        btn_7->setObjectName(QString::fromUtf8("btn_7"));

        horizontalLayout_2->addWidget(btn_7);

        btn_8 = new QToolButton(layoutWidget);
        btn_8->setObjectName(QString::fromUtf8("btn_8"));

        horizontalLayout_2->addWidget(btn_8);

        btn_9 = new QToolButton(layoutWidget);
        btn_9->setObjectName(QString::fromUtf8("btn_9"));

        horizontalLayout_2->addWidget(btn_9);

        btn_0 = new QToolButton(layoutWidget);
        btn_0->setObjectName(QString::fromUtf8("btn_0"));

        horizontalLayout_2->addWidget(btn_0);

        btn_minus = new QToolButton(layoutWidget);
        btn_minus->setObjectName(QString::fromUtf8("btn_minus"));

        horizontalLayout_2->addWidget(btn_minus);

        btn_add = new QToolButton(layoutWidget);
        btn_add->setObjectName(QString::fromUtf8("btn_add"));

        horizontalLayout_2->addWidget(btn_add);

        btn_backspace = new QToolButton(layoutWidget);
        btn_backspace->setObjectName(QString::fromUtf8("btn_backspace"));

        horizontalLayout_2->addWidget(btn_backspace);

        layoutWidget_2 = new QWidget(dockWidgetContents);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(51, 90, 531, 30));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        btn_tab = new QToolButton(layoutWidget_2);
        btn_tab->setObjectName(QString::fromUtf8("btn_tab"));

        horizontalLayout_3->addWidget(btn_tab);

        btn_q = new QToolButton(layoutWidget_2);
        btn_q->setObjectName(QString::fromUtf8("btn_q"));

        horizontalLayout_3->addWidget(btn_q);

        btn_w = new QToolButton(layoutWidget_2);
        btn_w->setObjectName(QString::fromUtf8("btn_w"));

        horizontalLayout_3->addWidget(btn_w);

        btn_e = new QToolButton(layoutWidget_2);
        btn_e->setObjectName(QString::fromUtf8("btn_e"));

        horizontalLayout_3->addWidget(btn_e);

        btn_r = new QToolButton(layoutWidget_2);
        btn_r->setObjectName(QString::fromUtf8("btn_r"));

        horizontalLayout_3->addWidget(btn_r);

        btn_t = new QToolButton(layoutWidget_2);
        btn_t->setObjectName(QString::fromUtf8("btn_t"));

        horizontalLayout_3->addWidget(btn_t);

        btn_y = new QToolButton(layoutWidget_2);
        btn_y->setObjectName(QString::fromUtf8("btn_y"));

        horizontalLayout_3->addWidget(btn_y);

        btn_u = new QToolButton(layoutWidget_2);
        btn_u->setObjectName(QString::fromUtf8("btn_u"));

        horizontalLayout_3->addWidget(btn_u);

        btn_i = new QToolButton(layoutWidget_2);
        btn_i->setObjectName(QString::fromUtf8("btn_i"));

        horizontalLayout_3->addWidget(btn_i);

        btn_o = new QToolButton(layoutWidget_2);
        btn_o->setObjectName(QString::fromUtf8("btn_o"));

        horizontalLayout_3->addWidget(btn_o);

        btn_p = new QToolButton(layoutWidget_2);
        btn_p->setObjectName(QString::fromUtf8("btn_p"));

        horizontalLayout_3->addWidget(btn_p);

        btn_leftbracket = new QToolButton(layoutWidget_2);
        btn_leftbracket->setObjectName(QString::fromUtf8("btn_leftbracket"));

        horizontalLayout_3->addWidget(btn_leftbracket);

        btn_rightbracket = new QToolButton(layoutWidget_2);
        btn_rightbracket->setObjectName(QString::fromUtf8("btn_rightbracket"));

        horizontalLayout_3->addWidget(btn_rightbracket);

        btn_splash = new QToolButton(layoutWidget_2);
        btn_splash->setObjectName(QString::fromUtf8("btn_splash"));

        horizontalLayout_3->addWidget(btn_splash);

        layoutWidget_3 = new QWidget(dockWidgetContents);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(51, 120, 531, 30));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        btn_caps = new QToolButton(layoutWidget_3);
        btn_caps->setObjectName(QString::fromUtf8("btn_caps"));

        horizontalLayout_4->addWidget(btn_caps);

        btn_a = new QToolButton(layoutWidget_3);
        btn_a->setObjectName(QString::fromUtf8("btn_a"));

        horizontalLayout_4->addWidget(btn_a);

        btn_s = new QToolButton(layoutWidget_3);
        btn_s->setObjectName(QString::fromUtf8("btn_s"));

        horizontalLayout_4->addWidget(btn_s);

        btn_d = new QToolButton(layoutWidget_3);
        btn_d->setObjectName(QString::fromUtf8("btn_d"));

        horizontalLayout_4->addWidget(btn_d);

        btn_f = new QToolButton(layoutWidget_3);
        btn_f->setObjectName(QString::fromUtf8("btn_f"));

        horizontalLayout_4->addWidget(btn_f);

        btn_g = new QToolButton(layoutWidget_3);
        btn_g->setObjectName(QString::fromUtf8("btn_g"));

        horizontalLayout_4->addWidget(btn_g);

        btn_h = new QToolButton(layoutWidget_3);
        btn_h->setObjectName(QString::fromUtf8("btn_h"));

        horizontalLayout_4->addWidget(btn_h);

        btn_j = new QToolButton(layoutWidget_3);
        btn_j->setObjectName(QString::fromUtf8("btn_j"));

        horizontalLayout_4->addWidget(btn_j);

        btn_k = new QToolButton(layoutWidget_3);
        btn_k->setObjectName(QString::fromUtf8("btn_k"));

        horizontalLayout_4->addWidget(btn_k);

        btn_l = new QToolButton(layoutWidget_3);
        btn_l->setObjectName(QString::fromUtf8("btn_l"));

        horizontalLayout_4->addWidget(btn_l);

        btn_split = new QToolButton(layoutWidget_3);
        btn_split->setObjectName(QString::fromUtf8("btn_split"));

        horizontalLayout_4->addWidget(btn_split);

        btn_quote = new QToolButton(layoutWidget_3);
        btn_quote->setObjectName(QString::fromUtf8("btn_quote"));

        horizontalLayout_4->addWidget(btn_quote);

        btn_enter = new QToolButton(layoutWidget_3);
        btn_enter->setObjectName(QString::fromUtf8("btn_enter"));

        horizontalLayout_4->addWidget(btn_enter);

        layoutWidget_4 = new QWidget(dockWidgetContents);
        layoutWidget_4->setObjectName(QString::fromUtf8("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(51, 150, 531, 30));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget_4);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        btn_lshift = new QToolButton(layoutWidget_4);
        btn_lshift->setObjectName(QString::fromUtf8("btn_lshift"));

        horizontalLayout_5->addWidget(btn_lshift);

        btn_z = new QToolButton(layoutWidget_4);
        btn_z->setObjectName(QString::fromUtf8("btn_z"));

        horizontalLayout_5->addWidget(btn_z);

        btn_x = new QToolButton(layoutWidget_4);
        btn_x->setObjectName(QString::fromUtf8("btn_x"));

        horizontalLayout_5->addWidget(btn_x);

        btn_c = new QToolButton(layoutWidget_4);
        btn_c->setObjectName(QString::fromUtf8("btn_c"));

        horizontalLayout_5->addWidget(btn_c);

        btn_v = new QToolButton(layoutWidget_4);
        btn_v->setObjectName(QString::fromUtf8("btn_v"));

        horizontalLayout_5->addWidget(btn_v);

        btn_b = new QToolButton(layoutWidget_4);
        btn_b->setObjectName(QString::fromUtf8("btn_b"));

        horizontalLayout_5->addWidget(btn_b);

        btn_n = new QToolButton(layoutWidget_4);
        btn_n->setObjectName(QString::fromUtf8("btn_n"));

        horizontalLayout_5->addWidget(btn_n);

        btn_m = new QToolButton(layoutWidget_4);
        btn_m->setObjectName(QString::fromUtf8("btn_m"));

        horizontalLayout_5->addWidget(btn_m);

        btn_lessthan = new QToolButton(layoutWidget_4);
        btn_lessthan->setObjectName(QString::fromUtf8("btn_lessthan"));

        horizontalLayout_5->addWidget(btn_lessthan);

        btn_greaterthan = new QToolButton(layoutWidget_4);
        btn_greaterthan->setObjectName(QString::fromUtf8("btn_greaterthan"));

        horizontalLayout_5->addWidget(btn_greaterthan);

        btn_quest = new QToolButton(layoutWidget_4);
        btn_quest->setObjectName(QString::fromUtf8("btn_quest"));

        horizontalLayout_5->addWidget(btn_quest);

        btn_rshift = new QToolButton(layoutWidget_4);
        btn_rshift->setObjectName(QString::fromUtf8("btn_rshift"));

        horizontalLayout_5->addWidget(btn_rshift);

        layoutWidget_5 = new QWidget(dockWidgetContents);
        layoutWidget_5->setObjectName(QString::fromUtf8("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(51, 180, 531, 30));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget_5);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        btn_lctrl = new QToolButton(layoutWidget_5);
        btn_lctrl->setObjectName(QString::fromUtf8("btn_lctrl"));

        horizontalLayout_6->addWidget(btn_lctrl);

        btn_lwin = new QToolButton(layoutWidget_5);
        btn_lwin->setObjectName(QString::fromUtf8("btn_lwin"));

        horizontalLayout_6->addWidget(btn_lwin);

        btn_lalt = new QToolButton(layoutWidget_5);
        btn_lalt->setObjectName(QString::fromUtf8("btn_lalt"));

        horizontalLayout_6->addWidget(btn_lalt);

        btn_space = new QToolButton(layoutWidget_5);
        btn_space->setObjectName(QString::fromUtf8("btn_space"));

        horizontalLayout_6->addWidget(btn_space);

        btn_ralt = new QToolButton(layoutWidget_5);
        btn_ralt->setObjectName(QString::fromUtf8("btn_ralt"));

        horizontalLayout_6->addWidget(btn_ralt);

        btn_rwin = new QToolButton(layoutWidget_5);
        btn_rwin->setObjectName(QString::fromUtf8("btn_rwin"));

        horizontalLayout_6->addWidget(btn_rwin);

        btn_rctrl = new QToolButton(layoutWidget_5);
        btn_rctrl->setObjectName(QString::fromUtf8("btn_rctrl"));

        horizontalLayout_6->addWidget(btn_rctrl);

        layoutWidget_6 = new QWidget(dockWidgetContents);
        layoutWidget_6->setObjectName(QString::fromUtf8("layoutWidget_6"));
        layoutWidget_6->setGeometry(QRect(600, 180, 121, 28));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget_6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        btn_left = new QToolButton(layoutWidget_6);
        btn_left->setObjectName(QString::fromUtf8("btn_left"));

        horizontalLayout_8->addWidget(btn_left);

        btn_down = new QToolButton(layoutWidget_6);
        btn_down->setObjectName(QString::fromUtf8("btn_down"));

        horizontalLayout_8->addWidget(btn_down);

        btn_right = new QToolButton(layoutWidget_6);
        btn_right->setObjectName(QString::fromUtf8("btn_right"));

        horizontalLayout_8->addWidget(btn_right);

        btn_up = new QToolButton(dockWidgetContents);
        btn_up->setObjectName(QString::fromUtf8("btn_up"));
        btn_up->setGeometry(QRect(641, 145, 36, 31));
        tvkey_out = new QLabel(dockWidgetContents);
        tvkey_out->setObjectName(QString::fromUtf8("tvkey_out"));
        tvkey_out->setGeometry(QRect(60, -2, 811, 21));
        btn_setcommit = new QPushButton(dockWidgetContents);
        btn_setcommit->setObjectName(QString::fromUtf8("btn_setcommit"));
        btn_setcommit->setGeometry(QRect(770, 180, 91, 30));
        btn_setcancel = new QPushButton(dockWidgetContents);
        btn_setcancel->setObjectName(QString::fromUtf8("btn_setcancel"));
        btn_setcancel->setGeometry(QRect(770, 140, 91, 30));
        layoutWidget1 = new QWidget(dockWidgetContents);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(51, 30, 531, 30));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btn_esc = new QToolButton(layoutWidget1);
        btn_esc->setObjectName(QString::fromUtf8("btn_esc"));

        horizontalLayout->addWidget(btn_esc);

        btn_f1 = new QToolButton(layoutWidget1);
        btn_f1->setObjectName(QString::fromUtf8("btn_f1"));

        horizontalLayout->addWidget(btn_f1);

        btn_f2 = new QToolButton(layoutWidget1);
        btn_f2->setObjectName(QString::fromUtf8("btn_f2"));

        horizontalLayout->addWidget(btn_f2);

        btn_f3 = new QToolButton(layoutWidget1);
        btn_f3->setObjectName(QString::fromUtf8("btn_f3"));

        horizontalLayout->addWidget(btn_f3);

        btn_f4 = new QToolButton(layoutWidget1);
        btn_f4->setObjectName(QString::fromUtf8("btn_f4"));

        horizontalLayout->addWidget(btn_f4);

        btn_f5 = new QToolButton(layoutWidget1);
        btn_f5->setObjectName(QString::fromUtf8("btn_f5"));

        horizontalLayout->addWidget(btn_f5);

        btn_f6 = new QToolButton(layoutWidget1);
        btn_f6->setObjectName(QString::fromUtf8("btn_f6"));

        horizontalLayout->addWidget(btn_f6);

        btn_f7 = new QToolButton(layoutWidget1);
        btn_f7->setObjectName(QString::fromUtf8("btn_f7"));

        horizontalLayout->addWidget(btn_f7);

        btn_f8 = new QToolButton(layoutWidget1);
        btn_f8->setObjectName(QString::fromUtf8("btn_f8"));

        horizontalLayout->addWidget(btn_f8);

        btn_f9 = new QToolButton(layoutWidget1);
        btn_f9->setObjectName(QString::fromUtf8("btn_f9"));

        horizontalLayout->addWidget(btn_f9);

        btn_f10 = new QToolButton(layoutWidget1);
        btn_f10->setObjectName(QString::fromUtf8("btn_f10"));

        horizontalLayout->addWidget(btn_f10);

        btn_f11 = new QToolButton(layoutWidget1);
        btn_f11->setObjectName(QString::fromUtf8("btn_f11"));

        horizontalLayout->addWidget(btn_f11);

        btn_f12 = new QToolButton(layoutWidget1);
        btn_f12->setObjectName(QString::fromUtf8("btn_f12"));

        horizontalLayout->addWidget(btn_f12);

        layoutWidget2 = new QWidget(dockWidgetContents);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(601, 30, 111, 28));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        btn_ptsr = new QToolButton(layoutWidget2);
        btn_ptsr->setObjectName(QString::fromUtf8("btn_ptsr"));

        horizontalLayout_7->addWidget(btn_ptsr);

        btn_del = new QToolButton(layoutWidget2);
        btn_del->setObjectName(QString::fromUtf8("btn_del"));

        horizontalLayout_7->addWidget(btn_del);

        btn_ins = new QToolButton(layoutWidget2);
        btn_ins->setObjectName(QString::fromUtf8("btn_ins"));

        horizontalLayout_7->addWidget(btn_ins);

        dockKeyboard->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(Qt::BottomDockWidgetArea, dockKeyboard);

        menubar->addAction(menuFile->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(actionOpen_Device);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionOpen_Device->setText(QCoreApplication::translate("MainWindow", "Open Device", nullptr));
        btn_testkey1->setText(QCoreApplication::translate("MainWindow", "KEY1", nullptr));
        btn_testkey2->setText(QCoreApplication::translate("MainWindow", "KEY2", nullptr));
        btn_testkey1_2->setText(QCoreApplication::translate("MainWindow", "KEY3", nullptr));
        btn_testkey2_2->setText(QCoreApplication::translate("MainWindow", "KEY4", nullptr));
        btn_testkey2_3->setText(QCoreApplication::translate("MainWindow", "KEY5", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Test", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "OneKey", nullptr));
        btn_setcancel_2->setText(QCoreApplication::translate("MainWindow", "Burn", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        btn_wave->setText(QCoreApplication::translate("MainWindow", "~", nullptr));
        btn_1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        btn_2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        btn_3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        btn_4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        btn_5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        btn_6->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        btn_7->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        btn_8->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        btn_9->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        btn_0->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        btn_minus->setText(QCoreApplication::translate("MainWindow", "_", nullptr));
        btn_add->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        btn_backspace->setText(QCoreApplication::translate("MainWindow", "Backspace", nullptr));
        btn_tab->setText(QCoreApplication::translate("MainWindow", "Tab", nullptr));
        btn_q->setText(QCoreApplication::translate("MainWindow", "Q", nullptr));
        btn_w->setText(QCoreApplication::translate("MainWindow", "W", nullptr));
        btn_e->setText(QCoreApplication::translate("MainWindow", "E", nullptr));
        btn_r->setText(QCoreApplication::translate("MainWindow", "R", nullptr));
        btn_t->setText(QCoreApplication::translate("MainWindow", "T", nullptr));
        btn_y->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        btn_u->setText(QCoreApplication::translate("MainWindow", "U", nullptr));
        btn_i->setText(QCoreApplication::translate("MainWindow", "I", nullptr));
        btn_o->setText(QCoreApplication::translate("MainWindow", "O", nullptr));
        btn_p->setText(QCoreApplication::translate("MainWindow", "P", nullptr));
        btn_leftbracket->setText(QCoreApplication::translate("MainWindow", "[", nullptr));
        btn_rightbracket->setText(QCoreApplication::translate("MainWindow", "]", nullptr));
        btn_splash->setText(QCoreApplication::translate("MainWindow", "\\", nullptr));
        btn_caps->setText(QCoreApplication::translate("MainWindow", "Caps ", nullptr));
        btn_a->setText(QCoreApplication::translate("MainWindow", "A", nullptr));
        btn_s->setText(QCoreApplication::translate("MainWindow", "S", nullptr));
        btn_d->setText(QCoreApplication::translate("MainWindow", "D", nullptr));
        btn_f->setText(QCoreApplication::translate("MainWindow", "F", nullptr));
        btn_g->setText(QCoreApplication::translate("MainWindow", "G", nullptr));
        btn_h->setText(QCoreApplication::translate("MainWindow", "H", nullptr));
        btn_j->setText(QCoreApplication::translate("MainWindow", "J", nullptr));
        btn_k->setText(QCoreApplication::translate("MainWindow", "K", nullptr));
        btn_l->setText(QCoreApplication::translate("MainWindow", "L", nullptr));
        btn_split->setText(QCoreApplication::translate("MainWindow", ";", nullptr));
        btn_quote->setText(QCoreApplication::translate("MainWindow", "'", nullptr));
        btn_enter->setText(QCoreApplication::translate("MainWindow", " Enter ", nullptr));
        btn_lshift->setText(QCoreApplication::translate("MainWindow", "  Shift  ", nullptr));
        btn_z->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        btn_x->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        btn_c->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        btn_v->setText(QCoreApplication::translate("MainWindow", "V", nullptr));
        btn_b->setText(QCoreApplication::translate("MainWindow", "B", nullptr));
        btn_n->setText(QCoreApplication::translate("MainWindow", "N", nullptr));
        btn_m->setText(QCoreApplication::translate("MainWindow", "M", nullptr));
        btn_lessthan->setText(QCoreApplication::translate("MainWindow", "<", nullptr));
        btn_greaterthan->setText(QCoreApplication::translate("MainWindow", ">", nullptr));
        btn_quest->setText(QCoreApplication::translate("MainWindow", "?", nullptr));
        btn_rshift->setText(QCoreApplication::translate("MainWindow", "  Shift  ", nullptr));
        btn_lctrl->setText(QCoreApplication::translate("MainWindow", " Ctrl ", nullptr));
        btn_lwin->setText(QCoreApplication::translate("MainWindow", "Win", nullptr));
        btn_lalt->setText(QCoreApplication::translate("MainWindow", "Alt", nullptr));
        btn_space->setText(QCoreApplication::translate("MainWindow", "                Space                ", nullptr));
        btn_ralt->setText(QCoreApplication::translate("MainWindow", "Alt", nullptr));
        btn_rwin->setText(QCoreApplication::translate("MainWindow", "Win", nullptr));
        btn_rctrl->setText(QCoreApplication::translate("MainWindow", " Ctrl", nullptr));
        btn_left->setText(QCoreApplication::translate("MainWindow", "<", nullptr));
        btn_down->setText(QCoreApplication::translate("MainWindow", " v ", nullptr));
        btn_right->setText(QCoreApplication::translate("MainWindow", ">", nullptr));
        btn_up->setText(QCoreApplication::translate("MainWindow", "^", nullptr));
        tvkey_out->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        btn_setcommit->setText(QCoreApplication::translate("MainWindow", "Commit", nullptr));
        btn_setcancel->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
        btn_esc->setText(QCoreApplication::translate("MainWindow", "Esc", nullptr));
        btn_f1->setText(QCoreApplication::translate("MainWindow", "F1", nullptr));
        btn_f2->setText(QCoreApplication::translate("MainWindow", "F2", nullptr));
        btn_f3->setText(QCoreApplication::translate("MainWindow", "F3", nullptr));
        btn_f4->setText(QCoreApplication::translate("MainWindow", "F4", nullptr));
        btn_f5->setText(QCoreApplication::translate("MainWindow", "F5", nullptr));
        btn_f6->setText(QCoreApplication::translate("MainWindow", "F6", nullptr));
        btn_f7->setText(QCoreApplication::translate("MainWindow", "F7", nullptr));
        btn_f8->setText(QCoreApplication::translate("MainWindow", "F8", nullptr));
        btn_f9->setText(QCoreApplication::translate("MainWindow", "F9", nullptr));
        btn_f10->setText(QCoreApplication::translate("MainWindow", "F10", nullptr));
        btn_f11->setText(QCoreApplication::translate("MainWindow", "F11", nullptr));
        btn_f12->setText(QCoreApplication::translate("MainWindow", "F12", nullptr));
        btn_ptsr->setText(QCoreApplication::translate("MainWindow", "PtSr", nullptr));
        btn_del->setText(QCoreApplication::translate("MainWindow", "Del", nullptr));
        btn_ins->setText(QCoreApplication::translate("MainWindow", "Ins", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
