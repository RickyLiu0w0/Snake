#-------------------------------------------------
#
# Project created by QtCreator 2019-08-03T15:51:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Snake
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
        datahelper.cpp \
        food.cpp \
        foodunit.cpp \
        gamewidget.cpp \
        main.cpp \
        player.cpp \
        snake.cpp \
        snakeunit.cpp \
        unit.cpp \
        wall.cpp \
        wallunit.cpp \
        widget.cpp

HEADERS += \
        datahelper.h \
        food.h \
        foodunit.h \
        gamewidget.h \
        player.h \
        snake.h \
        snakeunit.h \
        unit.h \
        wall.h \
        wallunit.h \
        widget.h

FORMS += \
        gamewidget.ui \
        widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
