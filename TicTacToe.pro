#-------------------------------------------------
#
# Project created by QtCreator 2018-06-01T18:02:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TicTacToe
TEMPLATE = app


SOURCES += main.cpp\
        tictactoe.cpp \
    scoreboard.cpp \
    setting.cpp \
    board.cpp \
    developer.cpp \
    about.cpp \
    finalboard.cpp \
    aiboard.cpp

HEADERS  += tictactoe.h \
    scoreboard.h \
    setting.h \
    board.h \
    developer.h \
    about.h \
    finalboard.h \
    aiboard.h

FORMS    += tictactoe.ui \
    scoreboard.ui \
    setting.ui \
    board.ui \
    developer.ui\
    about.ui \
    finalboard.ui

RESOURCES += \
    images.qrc
TRANSLATIONS += tictactoe_hi.ts \
    tictactoe_en_us.ts
