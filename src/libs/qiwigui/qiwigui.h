#ifndef QIWIGUI_H
#define QIWIGUI_H
#include <QObject>
#include <QImage>
#include <QByteArray>
#include "qiwigui_global.h"

namespace Qiwi {

class QIWIGUISHARED_EXPORT QiwiGuiUtils {
  public:

    static const QImage pdf2image(const QByteArray &data);
};

}

#endif // QIWIGUI_H
