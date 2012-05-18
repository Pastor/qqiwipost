#include <QSplitter>
#include <QLayout>
#include "qiwigui.h"
#include "qiwipostmain.h"
#include "ui_qiwipostmain.h"

using namespace Qiwi;

QiwiPostMain::QiwiPostMain(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::QiwiPostMain),
  mw(new QiwiGuiMachineView(this)),  pm(new QiwiPostPackageTableModel(this)),
  tvPackages(new QTableView(this)), post(new QiwiPost(this)),
  tabs(new QiwiPostTabs(this)), packView(new QiwiPostPackageView(this)) {
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
}

QiwiPostMain::~QiwiPostMain() {
  delete ui;
  delete mw;
  delete pm;
  delete post;
  delete tabs;
  delete packView;
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
  PackageCollection collection = post->loadPackages(error);
  if ( error.hasError ) {
    QiwiGuiUtils::show(error, this);
  } else {
    pm->load( collection.packages );
    for (int i = 0; i < pm->rowCount(); ++i) {
      tvPackages->setRowHeight(i, 22);
    }
    tvPackages->setColumnHidden(1,  true);
    tvPackages->setColumnHidden(2,  true);
    tvPackages->setColumnHidden(3,  true);
    tvPackages->setColumnHidden(4,  true);
    tvPackages->setColumnHidden(5,  true);
    tvPackages->setColumnHidden(6,  true);
    tvPackages->setColumnHidden(8,  true);
    tvPackages->setColumnHidden(9,  true);
    tvPackages->setColumnHidden(10,  true);
    tvPackages->setColumnHidden(11,  true);
    tvPackages->setColumnHidden(12,  true);
    tvPackages->setColumnHidden(13,  true);
    tvPackages->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
  }
  tabs->setEnabledUpdatePackage(true);
}

void
QiwiPostMain::selectMachines() {
  mw->listUpdate(post);
  mw->exec();
}

void
QiwiPostMain::currentRowChanged(const QModelIndex &current,
                                const QModelIndex &previous) {
  const Package package = pm->rowAt(current.row());
  packView->load(post, package);
}
