QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    configform.cpp \
    configsaver.cpp \
    configwindow.cpp \
    customkey.cpp \
    customkeyboard.cpp \
    devicefinder.cpp \
    hidcodetable.cpp \
    keyvalue.cpp \
    main.cpp \
    mainwindow.cpp \
    userconfig.cpp

HEADERS += \
    configform.h \
    configsaver.h \
    configwindow.h \
    customkey.h \
    customkeyboard.h \
    devicefinder.h \
    hidapi.h \
    hidcodetable.h \
    keyvalue.h \
    mainwindow.h \
    userconfig.h

FORMS += \
    configform.ui \
    configwindow.ui \
    devicefinder.ui \
    mainwindow.ui

LIBS += -L$$_PRO_FILE_PWD_/  -l hidapi

TRANSLATIONS += trans_zh_CN.ts
TRANSLATIONS += trans_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    trans_en_US.ts \
    trans_zh_CN.ts
RC_FILE = logo.rc
