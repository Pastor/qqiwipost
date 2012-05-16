#ifndef QIWIPOSTREQUESTER_P_H
#define QIWIPOSTREQUESTER_P_H
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include "qiwipostrequester.h"

namespace Qiwi {
namespace Internal {
  class QiwiPostRequesterPrivate: public QObject {
    Q_OBJECT
  public:
    QiwiPostRequesterPrivate();
    ~QiwiPostRequesterPrivate();

    QUrl prepareUrl(const QString &method, const QueryParams &params) const;
    QByteArray prepareParams(const QueryParams &params) const;

    QNetworkAccessManager *m;
    QUrl url;
    QString username;
    QString password;
    QByteArray result;
    QString error;
    QList< QPair<QByteArray, QByteArray> > replayHeaders;
    volatile bool workComplete;
  protected slots:
    void finished(QNetworkReply *replay);
  };
}
}

#endif // QIWIPOSTREQUESTER_P_H
