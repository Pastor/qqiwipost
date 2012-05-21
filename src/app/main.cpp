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
#include <QtCore/QFile>

#include <QtNetwork/QNetworkProxyFactory>

#include <QtGui/QApplication>
#include <QtGui/QDesktopServices>
#include <QtGui/QMainWindow>
#include <QtGui/QMessageBox>
#include <QtGui/QImage>

//#include <qiwipost/qiwipostrequester.h>

//#include <qiwipost/qiwipost.h>
#include <qiwigui/qiwigui.h>
#include <qiwigui/qiwipostmain.h>

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
    QObject::connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
    Qiwi::QiwiPostMain *pmain = new Qiwi::QiwiPostMain();
    pmain->loadSettings(shareDir.absoluteFilePath("qiwipost.db"));
    pmain->applaySettings();
    shareDir.cdUp();
    shareDir.cd("plugins");
    QApplication::addLibraryPath(shareDir.absolutePath());
    pmain->setWindowState(Qt::WindowMaximized);
    //Qiwi::QiwiGuiUtils::setToolStyle(pmain);
    pmain->show();
    pmain->reload();
    int result = app.exec();
    pmain->saveSettings();
    //delete pmain;
    return result;
}
