TARGET = QiwiGui
TEMPLATE = lib

include(../../library.pri)
#include(../../3rdparty/libpoppler.pri)

LIBS *= -l$$qtLibraryName(QiwiPost) -lUser32

DEFINES += QIWIGUI_LIBRARY

SOURCES += qiwigui.cpp \
    qiwiguimodel.cpp \
    qiwiguimachineview.cpp \
    qiwierrorview.cpp

HEADERS += qiwigui.h\
        qiwigui_global.h \
    qiwiguimodel.h \
    qiwiguimachineview.h \
    qiwierrorview.h

FORMS += \
    qiwiguimachineview.ui \
    qiwierrorview.ui









