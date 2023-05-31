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
    Forms/configform.cpp \
    Utils/configsaver.cpp \
    Utils/customkey.cpp \
    Utils/customkeyboard.cpp \
    Forms/devicefinder.cpp \
    HidAPI/hidapi.c \
    HidAPI/hidcodetable.cpp \
    Utils/keyvalue.cpp \
    main.cpp \
    Forms/settingform.cpp \
    UIpainter/uipainter.cpp \
    Utils/userconfig.cpp

HEADERS += \
    Forms/configform.h \
    Utils/configsaver.h \
    Utils/customkey.h \
    Utils/customkeyboard.h \
    Forms/devicefinder.h \
    HidAPI/hidapi.h \
    HidAPI/hidcodetable.h \
    Utils/keyvalue.h \
    Forms/settingform.h \
    UIpainter/uipainter.h \
    Utils/userconfig.h

FORMS += \
    Forms/configform.ui \
    Forms/devicefinder.ui \
    Forms/settingform.ui

LIBS += -L$$_PRO_FILE_PWD_/  libs/libusb-1.0
LIBS +=  -lsetupapi


TRANSLATIONS += lang/trans_zh_CN.ts
TRANSLATIONS += lang/trans_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    lang/trans_en_US.ts \
    lang/trans_zh_CN.ts
RC_FILE = logo.rc
