#include <QDebug>
#include <QTableWidgetItem>
#include <QDateTime>
#include <QMessageBox>
#include <qiwipost/dao.h>
#include <qiwigui/qiwigui.h>
#include "qiwipostsendpackages.h"
#include "ui_qiwipostsendpackages.h"

using namespace Qiwi;

QiwiPostSendPackages::QiwiPostSendPackages(QWidget *parent) :
  QDialog(parent), ui(new Ui::QiwiPostSendPackages), post(0) {
  ui->setupUi(this);

  QiwiGuiUtils::setToolStyle(this);

  connect(ui->pbRefresh, SIGNAL(clicked()), this, SLOT(reload()));
  connect(ui->pbSend, SIGNAL(clicked()), this, SLOT(sendPackages()));

  ui->twPackages->setColumnCount(2);
  QTableWidgetItem *item = new QTableWidgetItem(trUtf8("Name"));
  QFont font = item->font();
  font.setBold(true);
  item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
  item->setFont(font);
  ui->twPackages->setHorizontalHeaderItem(0, item);
  item = new QTableWidgetItem(trUtf8("Created"));
  item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
  item->setFont(font);
  ui->twPackages->setHorizontalHeaderItem(1, item);
  ui->twPackages->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
  ui->twPackages->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
}

QiwiPostSendPackages::~QiwiPostSendPackages() {
  delete ui;
}

void
QiwiPostSendPackages::show(QiwiPost *post) {
  this->post = post;  
  setModal(true);
  setVisible(true);
  reload();
}

void
QiwiPostSendPackages::reload() {
  ui->twPackages->clearContents();
  ui->twPackages->setRowCount(0);
  if ( post == 0 ) {
    qDebug() << "QiwiPostSendPackages::post == 0";
    return;
  }
  Error error;
  const PackageCollection pc = post->loadPackages(error, "Created");

  if ( error.hasError ) {
    QiwiGuiUtils::show(error, this);
    return;
  }

  if ( pc.packages.size() == 0 ) {
    QMessageBox::information(this,
                             trUtf8("Information"),
                             trUtf8("No registered premises"));
    reject();
    return;
  }

  PackageListIterator it(pc.packages);
  while ( it.hasNext() ) {
    const Package p = it.next();
    QTableWidgetItem *item = new QTableWidgetItem(p.packcode, QTableWidgetItem::UserType);
    item->setData( Qt::UserRole, qVariantFromValue<Package>(p) );
    item->setFlags( item->flags() | Qt::ItemIsUserCheckable );
    item->setCheckState(Qt::Checked);
    int row = ui->twPackages->rowCount();
    ui->twPackages->insertRow(row);
    ui->twPackages->setItem( row, 0, item );
    QDateTime createdDate = QDateTime::fromString(p.creationDate, Qt::ISODate);
    item = new QTableWidgetItem(createdDate.toString("dd.MM.yyyy hh:MM:ss"));
    ui->twPackages->setItem( row, 1, item );
    ui->twPackages->setRowHeight(row, 18);
  }
}

void
QiwiPostSendPackages::sendPackages() {
  QStringList list;
  for (int i = 0; i < ui->twPackages->rowCount(); ++i) {
    QTableWidgetItem *item = ui->twPackages->item(i, 0);
    if ( item ) {
      if ( item->checkState() == Qt::Checked ) {
        Package p = qVariantValue<Package>(item->data(Qt::UserRole));
        list << p.packcode;
      }
    }
  }

  if ( post == 0 ) {
    qDebug() << "QiwiPostSendPackages::post == 0";
    return;
  }

  Error error;
  QByteArray data = post->confirmPackages(error, list, ui->chbTestMode->isChecked());
  if ( error.hasError ) {
    QiwiGuiUtils::show(error, this);
    return;
  }
  QiwiGuiUtils::pdfView(data);
  accept();
}
