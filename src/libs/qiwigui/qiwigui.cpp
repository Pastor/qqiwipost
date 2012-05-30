#include <QFile>
#include <QTemporaryFile>
#include <QDesktopServices>
#include <QUrl>
#include "qiwierrorview.h"
#include "qiwigui.h"

#if defined(Q_OS_WIN)
#include <windows.h>
#endif

//#include <poppler/qt4/poppler-qt4.h>

using namespace Qiwi;

void
QiwiGuiUtils::setToolStyle(QWidget *widget) {
#if defined(Q_OS_WIN)
  LONG exStyle = GetWindowLong(widget->winId(), GWL_EXSTYLE);
  SetWindowLong( widget->winId(), GWL_EXSTYLE, exStyle | WS_EX_TOOLWINDOW );
#endif
}

const QImage
QiwiGuiUtils::pdf2image(const QByteArray &data) {
  Q_UNUSED(data);
//  QImage result;
//  Poppler::Document *doc = Poppler::Document::loadFromData(data);
//  if ( doc == 0 || doc->isLocked() ) {
//    delete doc;
//    return result;
//  }
//  Poppler::Page *page = doc->page(0);
//  if ( page == 0 ) {
//    delete doc;
//    return result;
//  }
//  result = page->renderToImage();
//  delete page;
//  delete doc;
//  return result;
  return QImage();
}

void
QiwiGuiUtils::pdfView(const QByteArray &data) {
  QTemporaryFile file("qiwipost_pdf_XXXXXXXXXXXXXXXX.pdf");
  file.setAutoRemove(false);
  if ( file.open() ) {
    file.write(data);
    file.flush();
    file.close();
    QDesktopServices::openUrl(
          QUrl("file:///" + file.fileName(),
          QUrl::TolerantMode) );
  }
}

void
QiwiGuiUtils::show(Error &error, QWidget *parent) {
  QiwiErrorView errorView(parent);
  errorView.showError(error);
}
