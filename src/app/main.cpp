#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QUrl>
#include <QtCore/QTextStream>
#include <QtCore/QFileInfo>
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtCore/QLibraryInfo>
#include <QtCore/QTranslator>
#include <QtCore/QSettings>
#include <QtCore/QVariant>
#include <QtCore/QThreadPool>

#include <QtNetwork/QNetworkProxyFactory>

#include <QtGui/QApplication>
#include <QtGui/QDesktopServices>
#include <QtGui/QMainWindow>
#include <QtGui/QMessageBox>

#include <qiwipost/qiwipostrequester.h>

static inline QDir
getSharePath() {
  QDir shareDir = QApplication::applicationDirPath();
#if defined(Q_OS_WIN)
  if (shareDir.dirName().toLower() == "bin")
      shareDir.cdUp();
  shareDir.cd("share");
  shareDir.cd("qiwiport");
#elif defined(Q_OS_MAC)
  if (shareDir.dirName() == "MacOS") {
      shareDir.cdUp();
  }
  shareDir.cd("Resources");
#endif
  return shareDir;
}

int
main(int argc, char **argv) {
#ifdef Q_WS_X11
    QApplication::setGraphicsSystem("raster");
#endif
    QApplication app(argc, argv);
    QTranslator translator;
    QTranslator qtTranslator;
    QDir shareDir = getSharePath();
    QString locale = QLocale::system().name();
    const QString &qiwiTrPath = shareDir.absoluteFilePath("translations");
    if (translator.load(QLatin1String("qiwipost_") + locale, qiwiTrPath)) {
        const QString &qtTrPath = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
        const QString &qtTrFile = QLatin1String("qt_") + locale;
        if (qtTranslator.load(qtTrFile, qtTrPath) || qtTranslator.load(qtTrFile, qiwiTrPath)) {
            app.installTranslator(&translator);
            app.installTranslator(&qtTranslator);
            app.setProperty("qiwipost_locale", locale);
        } else {
            translator.load(QString());
        }
    }

#if defined(Q_OS_UNIX)
    QUrl proxyUrl(QString::fromLatin1(qgetenv("http_proxy")));
    if (proxyUrl.isValid()) {
        QNetworkProxy proxy(QNetworkProxy::HttpProxy, proxyUrl.host(),
                            proxyUrl.port(), proxyUrl.userName(), proxyUrl.password());
        QNetworkProxy::setApplicationProxy(proxy);
    }
#if defined(Q_OS_MAC)
    else {
        QNetworkProxyFactory::setUseSystemConfiguration(true);
    }
#endif
#endif
    Qiwi::QiwiPostRequester *req = new Qiwi::QiwiPostRequester();
    Qiwi::QueryParams params;
    req->setUrl("http://apitest.qiwipost.ru");
    req->setUsername("8880000000");
    req->setPassword("test");
    req->request("listmachines_csv", params);
    req->wait();
    if ( req->hasError() ) {
        qDebug() << "Error: " << req->errorString();
    } else {
        QMessageBox::information(0, "INFO", req->result());
    }
    delete req;
    app.exit(-1);
    //return app.exec();
}
