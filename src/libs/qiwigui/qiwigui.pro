TARGET = QiwiGui
TEMPLATE = lib

include(../../library.pri)
#include(../../3rdparty/libpoppler.pri)

LIBS *= -l$$qtLibraryName(QiwiPost) -lUser32

DEFINES += QIWIGUI_LIBRARY

SOURCES += qiwigui.cpp \
    qiwiguimodel.cpp \
    qiwiguimachineview.cpp \
    qiwierrorview.cpp \
    qiwipostmain.cpp \
    qiwiposttabs.cpp \
    qiwipostpackageview.cpp

HEADERS += qiwigui.h\
        qiwigui_global.h \
    qiwiguimodel.h \
    qiwiguimachineview.h \
    qiwierrorview.h \
    qiwipostmain.h \
    qiwiposttabs.h \
    qiwipostpackageview.h

FORMS += \
    qiwiguimachineview.ui \
    qiwierrorview.ui \
    qiwipostmain.ui \
    qiwiposttabs.ui \
    qiwipostpackageview.ui

RESOURCES += \
    resource.qrc









