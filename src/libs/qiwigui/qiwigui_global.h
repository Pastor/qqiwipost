#ifndef QIWIGUI_GLOBAL_H
#define QIWIGUI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QIWIGUI_LIBRARY)
#  define QIWIGUISHARED_EXPORT Q_DECL_EXPORT
#else
#  define QIWIGUISHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QIWIGUI_GLOBAL_H
