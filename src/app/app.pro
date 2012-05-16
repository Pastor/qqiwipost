include(../../qiwi.pri)

TEMPLATE = app
TARGET = $$QIWI_APP_TARGET
DESTDIR = $$QIWI_APP_PATH

SOURCES += main.cpp

include(../rpath.pri)

LIBS *= -l$$qtLibraryName(QiwiPost)

win32 {
    RC_FILE = qiwipost.rc
    target.path = /bin
    INSTALLS += target
} else:macx {
    LIBS += -framework CoreFoundation
    ICON = qiwipost.icns
    info.input = Info.plist.in
    info.output = $$QIWI_BIN_PATH/../Info.plist
    QMAKE_SUBSTITUTES = info
} else {
    target.path  = /bin
    INSTALLS    += target
}

OTHER_FILES += qiwipost.rc \
    Info.plist.in
