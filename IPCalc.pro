TEMPLATE = app
TARGET = ipcalc

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ipaddress.cpp \
    main.cpp \
    application.cpp \
    calc.cpp \    
    mainwindow.cpp

HEADERS += \
    application.h \
    calc.h \
    ipaddress.h \
    mainwindow.h


RC_ICONS += ico/title.ico
RESOURCES += resource.qrc
