include(../qiwi.pri)

win32 {
    DLLDESTDIR = $$QIWI_APP_PATH
}

DESTDIR = $$QIWI_LIBRARY_PATH

include(rpath.pri)

TARGET = $$qtLibraryName($$TARGET)

contains(QT_CONFIG, reduce_exports):CONFIG += hide_symbols

!macx {
    win32 {
        target.path = /bin
        target.files = $$DESTDIR/$${TARGET}.dll
    } else {
        target.path = /$$QIWI_LIBRARY_BASENAME
    }
    INSTALLS += target
}
