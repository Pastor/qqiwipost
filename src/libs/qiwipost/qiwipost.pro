QT       += network sql xml
QT       -= gui

TARGET = QiwiPost
TEMPLATE = lib

include(../../library.pri)

DEFINES += QIWIPOST_LIBRARY

SOURCES += qiwipost.cpp \
    dao.cpp \
    qiwipostrequester.cpp

HEADERS += qiwipost.h\
        qiwipost_global.h \
    dao.h \
    qiwipostrequester.h \
    qiwipostrequester_p.h






