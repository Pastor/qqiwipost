!isEmpty(QIWI_PRI_INCLUDED):error("qiwi.pri already included")
QIWI_PRI_INCLUDED = 1

QIWI_VERSION = 1.0.0

defineReplace(cleanPath) {
    win32:1 ~= s|\\\\|/|g
    contains(1, ^/.*):pfx = /
    else:pfx =
    segs = $$split(1, /)
    out =
    for(seg, segs) {
        equals(seg, ..):out = $$member(out, 0, -2)
        else:!equals(seg, .):out += $$seg
    }
    return($$join(out, /, $$pfx))
}

defineReplace(targetPath) {
    return($$replace(1, /, $$QMAKE_DIR_SEP))
}

defineReplace(qtLibraryName) {
   unset(LIBRARY_NAME)
   LIBRARY_NAME = $$1
   CONFIG(debug, debug|release) {
      !debug_and_release|build_pass {
          mac:RET = $$member(LIBRARY_NAME, 0)_debug
              else:win32:RET = $$member(LIBRARY_NAME, 0)d
      }
   }
   isEmpty(RET):RET = $$LIBRARY_NAME
   return($$RET)
}

defineTest(minQtVersion) {
    maj = $$1
    min = $$2
    patch = $$3
    isEqual(QT_MAJOR_VERSION, $$maj) {
        isEqual(QT_MINOR_VERSION, $$min) {
            isEqual(QT_PATCH_VERSION, $$patch) {
                return(true)
            }
            greaterThan(QT_PATCH_VERSION, $$patch) {
                return(true)
            }
        }
        greaterThan(QT_MINOR_VERSION, $$min) {
            return(true)
        }
    }
    return(false)
}

# For use in custom compilers which just copy files
win32:i_flag = i
defineReplace(stripSrcDir) {
    win32 {
        !contains(1, ^.:.*):1 = $$OUT_PWD/$$1
    } else {
        !contains(1, ^/.*):1 = $$OUT_PWD/$$1
    }
    out = $$cleanPath($$1)
    out ~= s|^$$re_escape($$PWD/)||$$i_flag
    return($$out)
}

isEmpty(TEST):CONFIG(debug, debug|release) {
    !debug_and_release|build_pass {
        TEST = 1
    }
}

isEmpty(QIWI_LIBRARY_BASENAME) {
    QIWI_LIBRARY_BASENAME = lib
}

DEFINES += QIWI_LIBRARY_BASENAME=\\\"$$QIWI_LIBRARY_BASENAME\\\"

equals(TEST, 1) {
    QT += testlib
    DEFINES += WITH_TESTS
}

QIWI_SOURCE_TREE = $$PWD
isEmpty(QIWI_BUILD_TREE) {
    sub_dir = $$_PRO_FILE_PWD_
    sub_dir ~= s,^$$re_escape($$PWD),,
    QIWI_BUILD_TREE = $$cleanPath($$OUT_PWD)
    QIWI_BUILD_TREE ~= s,$$re_escape($$sub_dir)$,,
}
QIWI_APP_PATH = $$QIWI_BUILD_TREE/bin
QIWI_TEST_PATH = $$QIWI_APP_PATH
macx {
    QIWI_APP_TARGET   = "QiwiPost"
    QIWI_LIBRARY_PATH = $$QIWI_APP_PATH/$${QIWI_APP_TARGET}.app/Contents/PlugIns
    QIWI_PLUGIN_PATH  = $$QIWI_LIBRARY_PATH
    QIWI_LIBEXEC_PATH = $$QIWI_APP_PATH/$${QIWI_APP_TARGET}.app/Contents/Resources
    QIWI_DATA_PATH    = $$QIWI_APP_PATH/$${QIWI_APP_TARGET}.app/Contents/Resources
    QIWI_DOC_PATH     = $$QIWI_DATA_PATH/doc
    QIWI_BIN_PATH     = $$QIWI_APP_PATH/$${QIWI_APP_TARGET}.app/Contents/MacOS
    contains(QT_CONFIG, ppc):CONFIG += ppc x86
    copydata = 1
    isEmpty(TIGER_COMPAT_MODE) {
        QMAKE_CXXFLAGS *= -mmacosx-version-min=10.5
        QMAKE_LFLAGS *= -mmacosx-version-min=10.5
    }
} else {
    win32 {
        contains(TEMPLATE, vc.*)|contains(TEMPLATE_PREFIX, vc):vcproj = 1
        QIWI_APP_TARGET   = qiwipost
    } else {
        QIWI_APP_TARGET   = qiwipost
    }
    QIWI_LIBRARY_PATH = $$QIWI_BUILD_TREE/$$QIWI_LIBRARY_BASENAME
    QIWI_PLUGIN_PATH  = $$QIWI_LIBRARY_PATH/plugins
    QIWI_LIBEXEC_PATH = $$QIWI_APP_PATH # FIXME
    QIWI_DATA_PATH    = $$QIWI_BUILD_TREE/share/qiwipost
    QIWI_DOC_PATH     = $$QIWI_BUILD_TREE/share/doc/qiwipost
    QIWI_BIN_PATH     = $$QIWI_APP_PATH
    !isEqual(QIWI_SOURCE_TREE, $$QIWI_BUILD_TREE):copydata = 1
}

INCLUDEPATH += \
    $$QIWI_BUILD_TREE/src \
    $$QIWI_SOURCE_TREE/src/libs \
    $$QIWI_SOURCE_TREE/tools \
    $$QIWI_SOURCE_TREE/src/plugins

CONFIG += depend_includepath

LIBS += -L$$QIWI_LIBRARY_PATH

#DEFINES += QT_NO_CAST_FROM_ASCII
DEFINES += QT_NO_CAST_TO_ASCII
!macx:DEFINES += QT_USE_FAST_OPERATOR_PLUS QT_USE_FAST_CONCATENATION

unix {
    CONFIG(debug, debug|release):OBJECTS_DIR = $${OUT_PWD}/.obj/debug-shared
    CONFIG(release, debug|release):OBJECTS_DIR = $${OUT_PWD}/.obj/release-shared

    CONFIG(debug, debug|release):MOC_DIR = $${OUT_PWD}/.moc/debug-shared
    CONFIG(release, debug|release):MOC_DIR = $${OUT_PWD}/.moc/release-shared

    RCC_DIR = $${OUT_PWD}/.rcc
    UI_DIR = $${OUT_PWD}/.uic
}

win32-msvc* {
    #Don't warn about sprintf, fopen etc being 'unsafe'
    DEFINES += _CRT_SECURE_NO_WARNINGS
}
