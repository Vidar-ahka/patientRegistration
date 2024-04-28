QT       += core gui
QT += core network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# QXlsx code for Application Qt project





QXLSX_PARENTPATH= C:\QXlsx         # current QXlsx path is . (. means curret directory)
QXLSX_HEADERPATH=C:\QXlsx/header/  # current QXlsx header path is ./header/
QXLSX_SOURCEPATH=C:\QXlsx/source/  # current QXlsx source path is ./source/
include(C:\QXlsx/QXlsx.pri)

SOURCES += \
    addpatiets.cpp \
    avatar.cpp \
    bytearray.cpp \
    chatwindow.cpp \
    client.cpp \
    data.cpp \
    filemessagewidget.cpp \
    imageclick.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    message.cpp \
    messageinfo.cpp \
    messagewidget.cpp \
    patients.cpp \
    profil.cpp \
    user.cpp \
    userlist.cpp \
    users.cpp

HEADERS += \
    addpatiets.h \
    avatar.h \
    bytearray.h \
    chatwindow.h \
    client.h \
    data.h \
    filemessagewidget.h \
    imageclick.h \
    login.h \
    mainwindow.h \
    message.h \
    messageinfo.h \
    messagewidget.h \
    patients.h \
    profil.h \
    user.h \
    userlist.h \
    users.h

FORMS += \
    addpatiets.ui \
    avatar.ui \
    chatwindow.ui \
    filemessagewidget.ui \
    imageclick.ui \
    login.ui \
    mainwindow.ui \
    messagewidget.ui \
    patients.ui \
    profil.ui \
    user.ui \
    userlist.ui


# Default rules for deployment.

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target




INCLUDEPATH += $$PWD/../build-Telegram-Desktop_Qt_6_3_1_MinGW_64_bit-Debug/include
DEPENDPATH += $$PWD/../build-Telegram-Desktop_Qt_6_3_1_MinGW_64_bit-Debug/include

RESOURCES += \
    res.qrc
