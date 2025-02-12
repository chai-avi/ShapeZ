#-------------------------------------------------
#
# Project created by QtCreator 2023-11-26T22:54:19
#
#-------------------------------------------------

QT       += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShapeZ
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        shapez.cpp \
    map.cpp \
    installations.cpp \
    goods.cpp \
    tools.cpp \
    scenes.cpp \
    playscene.cpp \
    mypushbutton.cpp \
    actrules.cpp \
    startscene.cpp \
    shopscene.cpp

HEADERS += \
        shapez.h \
    config.h \
    map.h \
    installations.h \
    goods.h \
    tools.h \
    scenes.h \
    playscene.h \
    mypushbutton.h \
    actrules.h \
    startscene.h \
    shopscene.h

FORMS += \
        shapez.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc \
    res.qrc
