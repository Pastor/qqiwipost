
#include <QDateTime>
#include <qiwigui/qiwigui.h>
#include "qiwipostpackageview.h"
#include "ui_qiwipostpackageview.h"

namespace Qiwi {

}

using namespace Qiwi;

QiwiPostPackageView::QiwiPostPackageView(QWidget *parent) :
  QWidget(parent), ui(new Ui::QiwiPostPackageView), post(0) {
  ui->setupUi(this);

  ui->cbConfirm->addItem(trUtf8("No"));
  ui->cbConfirm->addItem(trUtf8("Yes"));

  ui->cbLabelCreated->addItem(trUtf8("No"));
  ui->cbLabelCreated->addItem(trUtf8("Yes"));
  setEnabledElements(false);

  connect(ui->pbPay, SIGNAL(clicked()),
          this, SLOT(pay()));
}

QiwiPostPackageView::~QiwiPostPackageView() {
  delete ui;
}

void
QiwiPostPackageView::load(QiwiPost *post, const Package &p) {
  this->post = post;
  pack = p;
  preinit(post);
  reset();
  ui->leAltMachineName->setText(p.alternativeBoxMachineName);
  ui->leAmountCharge->setText(p.amountCharged);
  ui->leCalculatedCharge->setText(p.calculatedChargeAmount);
  QDateTime createdDate = QDateTime::fromString(p.creationDate, Qt::ISODate);
  ui->leCreationDate->setText(createdDate.toString("dd.MM.yyyy hh:MM:ss"));
  ui->leDeliveryAmount->setText(p.onDeliveryAmount);
  ui->leFirstName->setText("");
  ui->leId->setText("");
  ui->leLabelCreationDate->setText(p.labelCreationDate);
  ui->leMachineName->setText(p.preferedBoxMachineName);
  ui->lePackCode->setText(p.packcode);
  ui->lePaymentStatus->setText(p.paymentStatus);
  ui->lePhone->setText(p.receiveremail);
  ui->leSecondName->setText("");
  const QString status = Package::packageStatus(p);
  ui->leStatus->setText(status);
  ui->leStatus->setToolTip(status);
  ui->cbConfirm->setCurrentIndex( p.isConfPrinted.toInt() );
  ui->cbLabelCreated->setCurrentIndex( p.labelPrinted.toInt() );

  for (int i = 0; i < ui->cbPackSize->count(); ++i) {
    if ( ui->cbPackSize->itemText(i) == p.packsize ) {
      ui->cbPackSize->setCurrentIndex(i);
      break;
    }
  }

  Purchase purchase = post->internalPurchasesByCode(p.packcode);
  ui->leFirstName->setText(purchase.fname);
  ui->leSecondName->setText(purchase.sname);
  setEnabledElements(false);
  ui->pbPay->setEnabled( p.status == "Created" );
}

const Package
QiwiPostPackageView::package(QiwiPost *post) const {
  Q_UNUSED(post);
  return Package();
}

const PackageReg
QiwiPostPackageView::packageReg(QiwiPost *post) const {
  Q_UNUSED(post);
  return PackageReg();
}

void
QiwiPostPackageView::preinit(QiwiPost *post) {

  if ( ui->cbPackSize->count() > 0 )
    return;
  Error error;
  const PriceCollection c = post->listPrices(error);
  if ( error.hasError ) {
    ui->cbPackSize->addItems(QStringList() << "A" << "B" << "C");
    ui->cbPackSize->setEditable(true);
    return;
  }
  ui->cbPackSize->setEditable(false);
  PriceListIterator it(c.prices);
  while ( it.hasNext() ) {
    const Price price = it.next();
    ui->cbPackSize->addItem(price.type);
  }
}

void
QiwiPostPackageView::setMode(Mode mode) {
  switch ( mode ) {
    case New:
      break;
    case Info:
      break;
    case Edit:
      break;
  }
}

void
QiwiPostPackageView::reset() {
  QListIterator<QWidget *> it( this->findChildren<QWidget *>() );
  while ( it.hasNext() ) {
    QWidget *w = it.next();
    if ( qobject_cast<QLineEdit *>(w) != 0 )
      qobject_cast<QLineEdit *>(w)->setText("");
    else if ( qobject_cast<QComboBox *>(w) != 0 )
      qobject_cast<QComboBox *>(w)->setCurrentIndex(0);
  }
}

void
QiwiPostPackageView::setEnabledElements(bool value) {
  QListIterator<QWidget *> it( this->findChildren<QWidget *>() );
  while ( it.hasNext() ) {
    QWidget *w = it.next();
    if ( qobject_cast<QLineEdit *>(w) != 0 )
      qobject_cast<QLineEdit *>(w)->setReadOnly(!value);
    else if ( qobject_cast<QComboBox *>(w) != 0 )
      qobject_cast<QComboBox *>(w)->setEnabled(value);
  }
}

void
QiwiPostPackageView::pay() {
  if ( post != 0 && !pack.packcode.isEmpty() ) {
    Error error;
    bool result = post->payPackage(error, pack.packcode);
    if ( !result || error.hasError ) {
      QiwiGuiUtils::show(error, this);
    } else {
      emit refresh();
    }
  }
}
