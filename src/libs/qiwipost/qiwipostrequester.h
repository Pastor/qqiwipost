#ifndef QIWIPOSTREQUESTER_H
#define QIWIPOSTREQUESTER_H

#include <QObject>
#include <QMap>
#include <QByteArray>
#include "qiwipost_global.h"

namespace Qiwi {
namespace Internal {
  class QiwiPostRequesterPrivate;
}
using namespace Internal;

typedef QMap<QString, QByteArray>         QueryParams;
typedef QMapIterator<QString, QByteArray> QueryParamsIterator;

class QIWIPOSTSHARED_EXPORT QiwiPostRequester : public QObject {
  Q_OBJECT
public:

  QiwiPostRequester(QObject *parent = 0);
  virtual ~QiwiPostRequester();

  void setUsername(const QString &username);
  void setPassword(const QString &password);
  void setUrl(const QString &url);

  void request(const QString &method,
               const QueryParams &getParams,
               const QueryParams &postParams);

  const QByteArray &result() const;

  bool hasError() const;

  const QString &errorString() const;

  void wait(quint64 msec = -1);

private:
  QiwiPostRequesterPrivate *d;
};

}

#endif // QIWIPOSTREQUESTER_H
