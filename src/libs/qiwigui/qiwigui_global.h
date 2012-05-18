#ifndef QIWIGUI_GLOBAL_H
#define QIWIGUI_GLOBAL_H

#include <QtGui/QWidget>
#include <QtCore/qglobal.h>

#if defined(Q_OS_WIN)
#include <windows.h>
#endif

#if defined(QIWIGUI_LIBRARY)
#  define QIWIGUISHARED_EXPORT Q_DECL_EXPORT
#else
#  define QIWIGUISHARED_EXPORT Q_DECL_IMPORT
#endif

namespace Qiwi {

  static inline void setToolStyle(QWidget *widget) {
#if defined(Q_OS_WIN)
  LONG exStyle = GetWindowLong(widget->winId(), GWL_EXSTYLE);
  SetWindowLong( widget->winId(), GWL_EXSTYLE, exStyle | WS_EX_TOOLWINDOW );
#endif
  }

}

#endif // QIWIGUI_GLOBAL_H
