#include <QMessageBox>
#include <qiwipost/dao.h>
#include <qiwigui/qiwigui.h>
#include "qiwipostregisterpackage.h"
#include "ui_qiwipostregisterpackage.h"

using namespace Qiwi;

QiwiPostRegisterPackage::QiwiPostRegisterPackage(QWidget *parent)
  : QDialog(parent), ui(new Ui::QiwiPostRegisterPackage),
    mw(new QiwiGuiMachineView(this)), rexv(new QRegExpValidator(this)),
    editMode(false) {
  ui->setupUi(this);
  QiwiGuiUtils::setToolStyle(this);
  connect(ui->pbCancel, SIGNAL(clicked()), this, SLOT(cancle()));
  connect(ui->pbRegister, SIGNAL(clicked()), this, SLOT(registerPackage()));
  connect(ui->pbSelectMachine, SIGNAL(clicked()), this, SLOT(selectMachine()));

  rexv->setRegExp(QRegExp("\\d{10}"));
  ui->lePhone->setValidator(rexv);

  ui->cbPackType->setEditable(false);
}

QiwiPostRegisterPackage::~QiwiPostRegisterPackage() {
  delete ui;
  delete mw;
  delete rexv;
}

int
QiwiPostRegisterPackage::show(QiwiPost *post, const Package &package) {
  this->post = post;
  this->editPackage = package;

  setWindowTitle(editMode ? trUtf8("Edit package") : trUtf8("Register package"));
  ui->pbRegister->setText(editMode ? trUtf8("Modify") : trUtf8("Register"));
  ui->leMachine->setText(editMode ? package.preferedBoxMachineName : "");
  ui->leOnDeliveryAmount->setText(editMode ? package.onDeliveryAmount : "");
  ui->lePhone->setText(editMode ? package.receiveremail : "");

  ui->teCustomRef->setText("");
  ui->leFirstName->setText("");
  ui->leSecondName->setText("");

  ui->cbPackType->clear();

  if ( ui->cbPackType->count() == 0 ) {
    Error error;
    const PriceCollection c = post->listPrices(error);
    if ( error.hasError ) {
      ui->cbPackType->addItems(QStringList() << "A" << "B" << "C");
    } else {
      PriceListIterator it(c.prices);
      while ( it.hasNext() ) {
        const Price price = it.next();
        ui->cbPackType->addItem(price.type);
      }
    }
  }

  if ( editMode ) {
    for (int i = 0; i < ui->cbPackType->count(); ++i) {
      if ( ui->cbPackType->itemText(i) == package.packsize ) {
        ui->cbPackType->setCurrentIndex(i);
        break;
      }
    }
    const Purchase p = post->internalPurchasesByCode(package.packcode);
    ui->leFirstName->setText(p.fname);
    ui->leSecondName->setText(p.sname);
    ui->teCustomRef->setText(p.customerRef);
  }


  ui->leMachine->setEnabled(!editMode);
  ui->leFirstName->setEnabled(!editMode);
  ui->leSecondName->setEnabled(!editMode);
  ui->leOnDeliveryAmount->setEnabled(!editMode);
  ui->lePhone->setEnabled(!editMode);
  ui->pbSelectMachine->setEnabled(!editMode);

  return exec();
}

void
QiwiPostRegisterPackage::registerPackage() {
  if ( editMode ) {
    const Purchase p = post->internalPurchasesByCode(editPackage.packcode);
    const QString customerRef = ui->teCustomRef->toPlainText();
    const QString packageSize = ui->cbPackType->currentText();
    Error error;
    bool isSuccessed = false;
    if ( editPackage.packsize != packageSize) {
      if ( !post->chanchePackageSize(error, editPackage.packcode, packageSize) ) {
        if ( error.hasError ) {
          QiwiGuiUtils::show(error, this);
        } else {
          QMessageBox::information(this,
                                   trUtf8("Information"),
                                   trUtf8("I can't change package size."));
        }
      } else {
        isSuccessed = true;
      }
    }
    if (customerRef != p.customerRef ) {
      QByteArray data = post->changePackageCustomerRef(error, editPackage.packcode, customerRef);
      if ( error.hasError ) {
        QiwiGuiUtils::show(error, this);
      } else {
        post->changePurchaseCustomerRef(p, customerRef);
        QiwiGuiUtils::pdfView(data);
        isSuccessed = true;
      }
    }

    if ( isSuccessed )
      accept();
  } else {
    if ( !isValid() )
      return;
    const QString firstName = ui->leFirstName->text();
    const QString secondName = ui->leSecondName->text();
    const QString machineName = ui->leMachine->text();
    const QString packageSize = ui->cbPackType->currentText();
    const QString onDelivery = ui->leOnDeliveryAmount->text();
    const QString customerRef = ui->teCustomRef->toPlainText();
    const QString phoneNumber = ui->lePhone->text();

    Error error;
    Purchase purchase;
    purchase.fname = firstName;
    purchase.sname = secondName;
    purchase.phone = phoneNumber;
    purchase.customerRef = customerRef;
    purchase = post->createPurchase(purchase);
    if ( purchase.id.isEmpty() ) {
      error.hasError = true;
      error.internalError = trUtf8("Can't create internal purchase\nError: %1")
          .arg(purchase.error);
      QiwiGuiUtils::show(error, this);
      return;
    }
    PackageReg reg;
    reg.addressPhoneNumber = phoneNumber;
    reg.boxMachineName = machineName;
    reg.customerRef = customerRef;
    reg.id = purchase.id;
    reg.onDeliveryAmount = onDelivery.isEmpty() ? "" : onDelivery;
    reg.packType = packageSize;
    reg.senderPhoneNumber = post->getProperty(QiwiPost::QIWIPOST_USERNAME);

    const PackageList list = post->registerPackage(error, reg);
    if ( error.hasError ) {
      QiwiGuiUtils::show(error, this);
      post->removeInternalPurchase(purchase.id);
      return;
    }
    if ( list.size() > 0 ) {
      Package p = list.at(0);
      if ( p.error.hasError ) {
        QiwiGuiUtils::show(p.error, this);
        post->removeInternalPurchase(purchase.id);
        return;
      } else {
        post->assignPurchase(purchase, p.packcode);
      }
    }
    accept();
  }
}

bool
QiwiPostRegisterPackage::isValid() const {
  return !ui->leFirstName->text().isEmpty() &&
      !ui->leSecondName->text().isEmpty() &&
      !ui->leMachine->text().isEmpty() &&
      ui->lePhone->text().size() == 10;
}

void
QiwiPostRegisterPackage::cancle() {
  reject();
}

void
QiwiPostRegisterPackage::selectMachine() {
  mw->listUpdate(post);
  if ( QDialog::Accepted == mw->exec() ) {
    ui->leMachine->setText(mw->selectedMachine().name);
  } else {
    ui->leMachine->setText("");
  }
}

void
QiwiPostRegisterPackage::setEditMode(bool value) {
  editMode = value;
}
