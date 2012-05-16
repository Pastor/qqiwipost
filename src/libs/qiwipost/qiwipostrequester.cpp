#include <QCoreApplication>
#include <QNetworkReply>
#include "qiwipostrequester.h"
#include "qiwipostrequester_p.h"

using namespace Qiwi;
using namespace Qiwi::Internal;

/** */
QiwiPostRequesterPrivate::QiwiPostRequesterPrivate()
  : m(new QNetworkAccessManager(this)), workComplete(true) {
  connect(m, SIGNAL(finished(QNetworkReply*)),
          this, SLOT(finished(QNetworkReply*)));
}

QiwiPostRequesterPrivate::~QiwiPostRequesterPrivate() {
  delete m;
}

QUrl
QiwiPostRequesterPrivate::prepareUrl(const QString &method) const {
  QUrl result(url);
  result.addQueryItem("do", method);
  return result;
}

QByteArray
QiwiPostRequesterPrivate::prepareParams(const QueryParams &params) const {
  QUrl urlParams;

  urlParams.addQueryItem("telephonenumber", username);
  urlParams.addQueryItem("password", password);
  QueryParamsIterator it(params);
  while ( it.hasNext() ) {
      it.next();
    QString key = it.key();
    QByteArray value = it.value();
    urlParams.addQueryItem(key, value);

  }
  return urlParams.encodedQuery();
}

void
QiwiPostRequesterPrivate::finished(QNetworkReply *replay) {
  result.clear();
  error.clear();
  replayHeaders.clear();
  result = replay->readAll();
  replayHeaders = replay->rawHeaderPairs();
  if ( replay->error() != QNetworkReply::NoError )
    error = replay->errorString();
  workComplete = true;
}

/** QiwiPostRequester */
QiwiPostRequester::QiwiPostRequester(QObject *parent)
  : QObject(parent), d(new QiwiPostRequesterPrivate) {
}

QiwiPostRequester::~QiwiPostRequester() {
  delete d;
}

void
QiwiPostRequester::setUsername(const QString &username) {
  d->username = username;
}

void
QiwiPostRequester::setPassword(const QString &password) {
  d->password = password;
}

void
QiwiPostRequester::setUrl(const QString &url) {
 d->url.setUrl(url);
}

void
QiwiPostRequester::request(const QString &method, const QueryParams &params) {
  QByteArray data = d->prepareParams(params);
  QUrl url = d->prepareUrl(method);
  QNetworkRequest req(url);
  req.setHeader(QNetworkRequest::ContentLengthHeader, data.size());
  req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
  d->m->post(req, data);
  d->workComplete = false;
}

void
QiwiPostRequester::wait() {
  while ( !d->workComplete )
    QCoreApplication::processEvents();
}

const QByteArray &
QiwiPostRequester::result() const {
  return d->result;
}

bool
QiwiPostRequester::hasError() const {
  return !d->error.isNull() && !d->error.isEmpty();
}

const QString &
QiwiPostRequester::errorString() const {
  return d->error;
}