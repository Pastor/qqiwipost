TARGET = QiwiGui
TEMPLATE = lib

include(../../library.pri)
include(../../3rdparty/libpoppler.pri)

DEFINES += QIWIGUI_LIBRARY

SOURCES += qiwigui.cpp

HEADERS += qiwigui.h\
        qiwigui_global.h

