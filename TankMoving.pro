#-------------------------------------------------
#
# Project created by QtCreator 2014-11-20T10:36:38
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TankMoving
TEMPLATE = app


SOURCES += main.cpp\
        Dialog.cpp \
    Scene.cpp \
    Square.cpp

HEADERS  += Dialog.h \
    Scene.h \
    Square.h

FORMS    += Dialog.ui

RESOURCES += \
    Textures.qrc
