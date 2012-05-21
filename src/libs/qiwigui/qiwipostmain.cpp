#include <QSplitter>
#include <QLayout>
#include <QMessageBox>
#include "qiwigui.h"
#include "qiwipostmain.h"
#include "ui_qiwipostmain.h"

using namespace Qiwi;

QiwiPostMain::QiwiPostMain(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::QiwiPostMain),
  pm(new QiwiPostPackageTableModel(this)),
  tvPackages(new QTableView(this)), post(new QiwiPost(this)),
  tabs(new QiwiPostTabs(this)), packView(new QiwiPostPackageView(this)),
  qps(new QiwiPostSettings(this)), qsp(new QiwiPostSendPackages(this)),
  qrp(new QiwiPostRegisterPackage(this)) {
  ui->setupUi(this);
  tvPackages->setModel(pm);
  tvPackages->setSelectionMode(QAbstractItemView::SingleSelection);
  tvPackages->setSelectionBehavior(QAbstractItemView::SelectRows);
  QVBoxLayout *layout = new QVBoxLayout();
  layout->setContentsMargins(2, 2, 2, 2);
  layout->setSpacing(2);
  ui->centralwidget->setLayout(layout);
  QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
  layout->addWidget(splitter);
  splitter->addWidget(tvPackages);
  splitter->addWidget(tabs);
  splitter->setLineWidth(10);
  tabs->setInfo(packView);

  connect(tvPackages->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
          this, SLOT(currentRowChanged(QModelIndex,QModelIndex)));
  connect(tabs, SIGNAL(updatePackages()),
          this, SLOT(reload()));
  connect(ui->actionCommon, SIGNAL(triggered()),
          this, SLOT(showSettings()));
  connect(tabs, SIGNAL(sendPackage()),
          this, SLOT(showSendPackages()));
  connect(tabs, SIGNAL(appendPackage()),
          this, SLOT(showRegisterPackage()));
  connect(tabs, SIGNAL(editPackage()),
          this, SLOT(showEditPackage()));
  connect(tabs, SIGNAL(removePackage()),
          this, SLOT(showUnregisterPackage()));

  tabs->setEnabledAppendPackage(true);
  tabs->setEnabledEditPackage(false);
  tabs->setEnabledRemovePackage(false);
  tabs->setEnabledSendPackage(true);
}

QiwiPostMain::~QiwiPostMain() {
  delete ui;
  delete pm;
  delete post;
  delete tabs;
  delete packView;
  delete qps;
  delete qsp;
  delete qrp;
}

void
QiwiPostMain::loadSettings(const QString &filename) {
  post->loadSettings(filename);
}

void
QiwiPostMain::applaySettings() {
  post->applaySettings();
}

void
QiwiPostMain::saveSettings() {
  post->saveSettings();
}

void
QiwiPostMain::reload() {
  Error error;
  tabs->setEnabledUpdatePackage(false);
  tvPackages->reset();
  pm->reset();
  for ( int i = 0; i < pm->columnCount(); ++i ) {
    tvPackages->setColumnHidden(i, true);
  }
  tvPackages->setColumnHidden(0,  false);
  tvPackages->setColumnHidden(7,  false);
  PackageCollection collection = post->loadPackages(error);
  if ( error.hasError ) {
    QiwiGuiUtils::show(error, this);
  } else {
    pm->load( collection.packages );
    for (int i = 0; i < pm->rowCount(); ++i) {
      tvPackages->setRowHeight(i, 22);
    }
    tvPackages->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    if ( pm->rowCount() > 0 )
      tvPackages->selectRow(0);
  }
  tabs->setEnabledUpdatePackage(true);
}

void
QiwiPostMain::selectMachines() {
  //mw->listUpdate(post);
  //mw->exec();
}

void
QiwiPostMain::currentRowChanged(const QModelIndex &current,
                                const QModelIndex &previous) {
  Q_UNUSED(previous);
  const Package package = pm->rowAt(current.row());
  tabs->setData(post, package);
  tabs->setEnabledAppendPackage(true);
  tabs->setEnabledEditPackage(false);
  tabs->setEnabledRemovePackage(false);
  tabs->setEnabledSendPackage(true);
  if ( package.status == "Created" ) {
    tabs->setEnabledEditPackage(true);
    tabs->setEnabledRemovePackage(true);
    tabs->setEnabledSendPackage(true);
  }
  currentPackage = package;
  packView->load(post, package);
}

void
QiwiPostMain::showSettings() {
  qps->show(post);
}

void
QiwiPostMain::showSendPackages() {
  qsp->show(post);
}

void
QiwiPostMain::showRegisterPackage() {
  qrp->setEditMode(false);
  if ( qrp->show(post, currentPackage) == QDialog::Accepted ) {
    reload();
  }
}

void
QiwiPostMain::showEditPackage() {
  qrp->setEditMode(true);
  if ( qrp->show(post, currentPackage) == QDialog::Accepted ) {
    reload();
  }
}

void
QiwiPostMain::showUnregisterPackage() {
  if ( currentPackage.packcode.isEmpty() )
    return;
  Error error;
  if ( !post->unregisterPackage(error, currentPackage.packcode) ) {
    if ( error.hasError ) {
      QiwiGuiUtils::show(error, this);
    } else {
      QMessageBox::critical(this,
                            trUtf8("Exception"),
                            trUtf8("Can't remove \"%1\" package")
                            .arg(currentPackage.packcode));
    }
  } else {
    post->removeInternalPurchase(currentPackage.id);
    QMessageBox::information(this,
                          trUtf8("Information"),
                          trUtf8("Package \"%1\" remove success")
                          .arg(currentPackage.packcode));
  }
}
