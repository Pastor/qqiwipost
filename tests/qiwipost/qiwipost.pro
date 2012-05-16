QT      += testlib
CONFIG  += qtestlib
TARGET   = testQiwiPost

include(../../qiwi.pri)
include(../../src/rpath.pri)

LIBS *= -l$$qtLibraryName(QiwiPost)

SOURCES  = testqiwipost.cpp

DESTDIR  = $$QIWI_TEST_PATH
