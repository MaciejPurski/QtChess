# Created by and for Qt Creator. This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtChess
TEMPLATE = app

HEADERS = \
   $$PWD/headers/board.h \
   $$PWD/headers/chessboard.h \
   $$PWD/headers/clock.h \
   $$PWD/headers/game.h \
   $$PWD/headers/gamestart.h \
   $$PWD/headers/mainwindow.h \
   $$PWD/headers/piece.h \
   $$PWD/headers/quitwindow.h

SOURCES = \
   $$PWD/sources/board.cpp \
   $$PWD/sources/chessboard.cpp \
   $$PWD/sources/clock.cpp \
   $$PWD/sources/game.cpp \
   $$PWD/sources/gamestart.cpp \
   $$PWD/sources/main.cpp \
   $$PWD/sources/mainwindow.cpp \
   $$PWD/sources/piece.cpp \
   $$PWD/sources/quitwindow.cpp

RESOURCES = \
   $$PWD/resources/board.png \
   $$PWD/resources/icons_white.png \
   $$PWD/resources/icons_black.png \

INCLUDEPATH = \
    $$PWD/headers

#DEFINES = 

FORMS += \
    mainwindow.ui

