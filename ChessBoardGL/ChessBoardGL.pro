#-------------------------------------------------
#
# Project created by QtCreator 2012-03-02T20:51:22
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = ChessBoardGL
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    chessboard.cpp \
    chessinfodialog.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    chessboard.h \
    chessinfodialog.h

FORMS += \
    chessinfodialog.ui
