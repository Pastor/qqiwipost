#include <QItemSelectionModel>
#include "qiwigui.h"
#include "qiwiguimachineview.h"
#include "ui_qiwiguimachineview.h"

using namespace Qiwi;

QiwiGuiMachineView::QiwiGuiMachineView(QWidget *parent)
  : QDialog(parent), ui(new Ui::QiwiGuiMachineView),
    mm(new QiwiPostMachineTableModel(this)) {
  ui->setupUi(this);
  ui->tvMachines->setModel(mm);
  QiwiGuiUtils::setToolStyle(this);
  connect(ui->pbSelect, SIGNAL(clicked()), this, SLOT(select()));
  connect(ui->tvMachines->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
          this, SLOT(currentRowChanged(QModelIndex,QModelIndex)));
  connect(this, SIGNAL(selectedMachine(Machine)),
          this, SLOT(triggeredMachine(Machine)));
}

QiwiGuiMachineView::~QiwiGuiMachineView() {
  delete ui;
}

void
QiwiGuiMachineView::listUpdate(QiwiPost *post) {
  Error error;
  MachineList list = post->loadMachines(error);
  if ( error.hasError ) {
    QiwiGuiUtils::show(error, this);
  } else {
    mm->load(list);
    for (int i = 0; i < mm->rowCount(); ++i) {
      ui->tvMachines->setRowHeight(i, 22);
    }
    ui->tvMachines->setColumnHidden(0,  true);
    ui->tvMachines->setColumnHidden(5,  true);
    ui->tvMachines->setColumnHidden(6,  true);
    ui->tvMachines->setColumnHidden(7,  true);
    ui->tvMachines->setColumnHidden(9,  true);
    ui->tvMachines->setColumnHidden(10, true);
    ui->tvMachines->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
  }
}

void
QiwiGuiMachineView::select() {
  accept();
}

const Machine
QiwiGuiMachineView::selectedMachine() const {
  QModelIndexList list = ui->tvMachines->selectionModel()->selectedRows();
  for ( int i = 0; i < list.count(); ++i ) {
    return mm->rowAt(list.at(i).row());
  }
  return Machine();
}

void
QiwiGuiMachineView::currentRowChanged(const QModelIndex &current,
                                      const QModelIndex &previous) {
  Q_UNUSED(previous);
  if ( current.row() >= mm->rowCount() )
    return;
  const Machine machine = mm->rowAt(current.row());
  emit selectedMachine(machine);
}

void
QiwiGuiMachineView::triggeredMachine(const Machine &machine) {
  ui->leName->setText(machine.name);
  ui->lePostCode->setText(machine.postcode);
  ui->leStreet->setText(machine.street);
  ui->leBuilding->setText(machine.buildingNumber);
  ui->leProvince->setText(machine.province);
  ui->leStatus->setText(machine.status);
  ui->leStreet->setText(machine.street);
  ui->leTown->setText(machine.town);
  ui->leWork->setText(machine.operatinghours);
  ui->teLocationDesc->setText(machine.locationDesc);
  ui->lePosition->setText(trUtf8("%1:%2").
                          arg(machine.latitude).
                          arg(machine.longitude));
}
