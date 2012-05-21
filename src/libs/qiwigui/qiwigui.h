#ifndef QIWIGUI_H
#define QIWIGUI_H
#include <QObject>
#include <QImage>
#include <QByteArray>
#include <qiwipost/dao.h>
#include "qiwigui_global.h"

namespace Qiwi {

class QIWIGUISHARED_EXPORT QiwiGuiUtils {
  public:

    static const QImage pdf2image(const QByteArray &data);
    static void pdfView(const QByteArray &data);
    static void show(Error &error, QWidget *parent = 0);
    static void setToolStyle(QWidget *widget);
};

}

#endif // QIWIGUI_H
