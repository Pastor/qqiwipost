#include <QLayout>
#include <QTemporaryFile>
#include <qiwigui/qiwigui.h>
#include "qiwiposttabs.h"
#include "ui_qiwiposttabs.h"

using namespace Qiwi;

QiwiPostTabs::QiwiPostTabs(QWidget *parent) :
  QWidget(parent), ui(new Ui::QiwiPostTabs), post(0) {
  ui->setupUi(this);
  QiwiGuiUtils::setToolStyle(this);
  connect(ui->pbRefresh, SIGNAL(clicked()),
          this, SLOT(proxy_updatePackages()));
  connect(ui->pbCRegister, SIGNAL(clicked()),
          this, SLOT(proxy_appendPackage()));
  connect(ui->pbUnregister, SIGNAL(clicked()),
          this, SLOT(proxy_removePackage()));
  connect(ui->pbEdit, SIGNAL(clicked()),
          this, SLOT(proxy_editPackage()));
  connect(ui->pbSend, SIGNAL(clicked()),
          this, SLOT(proxy_sendPackage()));
  connect(ui->pbOpen, SIGNAL(clicked()),
          this, SLOT(labelOpen()));
}

QiwiPostTabs::~QiwiPostTabs() {
  delete ui;
}

void
QiwiPostTabs::setInfo(QWidget *w) {
  QVBoxLayout *layout = new QVBoxLayout();
  ui->tbPackageInfo->setLayout(layout);
  layout->setContentsMargins(2, 2, 2, 2);
  layout->setSpacing(2);
  layout->addWidget(w);
}

void
QiwiPostTabs::setEnabledUpdatePackage(bool value) {
  ui->pbRefresh->setEnabled(value);
}

void QiwiPostTabs::setEnabledAppendPackage(bool value) {
  ui->pbCRegister->setEnabled(value);
}

void QiwiPostTabs::setEnabledRemovePackage(bool value) {
  ui->pbUnregister->setEnabled(value);
}

void QiwiPostTabs::setEnabledSendPackage(bool value) {
  ui->pbSend->setEnabled(value);
}

void QiwiPostTabs::setEnabledEditPackage(bool value) {
  ui->pbEdit->setEnabled(value);
}

void
QiwiPostTabs::proxy_updatePackages() {
  emit updatePackages();
}

void
QiwiPostTabs::proxy_appendPackage() {
  emit appendPackage();
}

void
QiwiPostTabs::proxy_removePackage() {
  emit removePackage();
}

void
QiwiPostTabs::proxy_sendPackage() {
  emit sendPackage();
}

void
QiwiPostTabs::proxy_editPackage() {
  emit editPackage();
}

void
QiwiPostTabs::setData(QiwiPost *post, const Package &package) {
  this->post = post;
  this->package = package;
  ui->pbOpen->setEnabled( post != 0 && !package.packcode.isEmpty() );
}

void
QiwiPostTabs::labelOpen() {
  if ( post == 0 || package.packcode.isEmpty() )
    return;
  Error error;
  QByteArray data = post->loadLabel(error, package.packcode);
  if ( error.hasError ) {
    QiwiGuiUtils::show(error, this);
  } else
    QiwiGuiUtils::pdfView(data);
}
