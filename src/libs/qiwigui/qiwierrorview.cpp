#include <qiwigui/qiwigui.h>
#include "qiwierrorview.h"
#include "ui_qiwierrorview.h"

using namespace Qiwi;

QiwiErrorView::QiwiErrorView(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QiwiErrorView) {
  ui->setupUi(this);
  QiwiGuiUtils::setToolStyle(this);
}

QiwiErrorView::~QiwiErrorView() {
  delete ui;
}


int
QiwiErrorView::showError(const Error &error) {
  ui->teError->clear();
  if ( error.hasError ) {
    if ( !error.internalError.isEmpty() ) {
      ui->pbSend->setEnabled(true);
      ui->teError->append(trUtf8("<h1 align = \"center\" style = \"color: red\">Internal error</h1>"));
      ui->teError->append(trUtf8("<h2 align = \"center\">%1</h2>").arg(error.internalError));
      ui->teError->append(QString(error.data));
    } else {
      ui->pbSend->setEnabled(false);
      ui->teError->append(trUtf8("<h1 align = \"center\" style = \"color: red\">Algorithm error</h1>"));
      ui->teError->append(trUtf8("<h2 align = \"center\">%1</h2>").arg(error.key));
      ui->teError->append(trUtf8("<h2 align = \"center\">%1</h2>").arg(error.desc));
    }
  } else {
    ui->teError->setText(trUtf8("Error empty"));
    ui->pbSend->setEnabled(false);
  }
  return exec();
}
