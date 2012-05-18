#include <QLayout>
#include "qiwiposttabs.h"
#include "ui_qiwiposttabs.h"

using namespace Qiwi;

QiwiPostTabs::QiwiPostTabs(QWidget *parent) :
  QWidget(parent), ui(new Ui::QiwiPostTabs) {
  ui->setupUi(this);

  connect(ui->pbRefresh, SIGNAL(clicked()),
          this, SLOT(proxy_updatePackages()));
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

void
QiwiPostTabs::proxy_updatePackages() {
  emit updatePackages();
}
