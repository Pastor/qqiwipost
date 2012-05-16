#include "qiwigui.h"

#include <poppler/qt4/poppler-qt4.h>

using namespace Qiwi;

const QImage
QiwiGuiUtils::pdf2image(const QByteArray &data) {
  QImage result;
  Poppler::Document *doc = Poppler::Document::loadFromData(data);
  if ( doc == 0 || doc->isLocked() ) {
    delete doc;
    return result;
  }
  Poppler::Page *page = doc->page(0);
  if ( page == 0 ) {
    delete doc;
    return result;
  }
  result = page->renderToImage();
  delete page;
  delete doc;
  return result;
}
