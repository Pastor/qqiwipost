#ifndef QIWIPOST_H
#define QIWIPOST_H
#include <QObject>
#include "qiwipost_global.h"

namespace Qiwi {
namespace Internal {
  class QiwiPostPrivate;
}
using namespace Internal;

class QIWIPOSTSHARED_EXPORT QiwiPost: public QObject {
  Q_OBJECT
public:
  QiwiPost(QObject *parent = 0);
  virtual ~QiwiPost();
private:
  QiwiPostPrivate *d;
};

}

#endif // QIWIPOST_H
