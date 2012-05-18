#include "qiwiguimodel.h"

using namespace Qiwi;

/**
  QString name;
  QString postcode;
  QString street;
  QString buildingNumber;
  QString town;
  QString latitude;
  QString longitude;
  QString locationDesc;
  QString province;
  QString status;
  QString operatinghours;

  */

QiwiGuiModel::QiwiGuiModel(QObject *parent)
  : QObject(parent) {
}

QiwiPostMachineTableModel::QiwiPostMachineTableModel(QObject *parent)
  : QAbstractTableModel(parent) {
  columns.append(trUtf8("Name"));
  columns.append(trUtf8("Town"));
  columns.append(trUtf8("PostCode"));
  columns.append(trUtf8("Street"));
  columns.append(trUtf8("buildingNumber"));

  columns.append(trUtf8("latitude"));
  columns.append(trUtf8("longitude"));
  columns.append(trUtf8("locationDesc"));
  columns.append(trUtf8("Province"));
  columns.append(trUtf8("Status"));
  columns.append(trUtf8("operatinghours"));
}

QiwiPostMachineTableModel::~QiwiPostMachineTableModel() {
}

QModelIndex
QiwiPostMachineTableModel::index(int row, int column, const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return createIndex(row, column);
}

QModelIndex
QiwiPostMachineTableModel::parent(const QModelIndex &child) const {
  Q_UNUSED(child);
  return QModelIndex();
}

int
QiwiPostMachineTableModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return machines.size();
}

int
QiwiPostMachineTableModel::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return columns.size();
}

QVariant
QiwiPostMachineTableModel::data(const QModelIndex &index, int role) const {
  if ( !index.isValid() )
    return QVariant();
  if (role != Qt::DisplayRole)
    return QVariant();

  if ( role == Qt::DisplayRole ) {
    const Machine machine = machines.at(index.row());
    const QString column = columns.at(index.column());
    if ( column == trUtf8("Name") ) {
      return machine.name;
    } else if ( column == trUtf8("PostCode") ) {
      return machine.postcode;
    } else if ( column == trUtf8("Street") ) {
      return machine.street;
    } else if ( column == trUtf8("buildingNumber") ) {
      return machine.buildingNumber;
    } else if ( column == trUtf8("Town") ) {
      return machine.town;
    } else if ( column == trUtf8("latitude") ) {
      return machine.latitude;
    } else if ( column == trUtf8("longitude") ) {
      return machine.longitude;
    } else if ( column == trUtf8("locationDesc") ) {
      return machine.locationDesc;
    } else if ( column == trUtf8("Province") ) {
      return machine.province;
    } else if ( column == trUtf8("Status") ) {
      return machine.status;
    } else if ( column == trUtf8("operatinghours") ) {
      return machine.operatinghours;
    } else {

    }
    return QVariant();
  }
  return QVariant();
}

QVariant
QiwiPostMachineTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    static QIcon operating(QPixmap(":/internal/images/16x16/server_connect.png"));
    static QIcon operating_none(QPixmap(":/internal/images/16x16/server.png"));
    if (role == Qt::DisplayRole) {
      if ( orientation == Qt::Vertical ) {
        return QVariant();
      }
      return columns.at(section);
    }
    if (role == Qt::DecorationRole) {
      if ( orientation == Qt::Vertical ) {
        const Machine machine = machines.at(section);
        if ( machine.status == "Operating" ) {
          return operating;
        } else
          return operating_none;
      }
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}

Qt::ItemFlags
QiwiPostMachineTableModel::flags(const QModelIndex &index) const {
    if ( !index.isValid() )
        return 0;
    return (Qt::ItemIsDragEnabled | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
}

void
QiwiPostMachineTableModel::load(const MachineList &list) {
  beginResetModel();
  machines.clear();
  machines.append(list);
  endResetModel();
}

const Machine
QiwiPostMachineTableModel::rowAt(int index) const {
  return machines.at(index);
}

/** class QiwiPostPackageTableModel */
/**
  QString packcode;
  QString packsize;
  QString amountCharged;
  QString calculatedChargeAmount;
  QString paymentStatus;
  QString creationDate;
  QString labelCreationDate;
  QString status;
  QString isConfPrinted;
  QString labelPrinted;
  QString onDeliveryAmount;
  QString preferedBoxMachineName;
  QString alternativeBoxMachineName;
  QString receiveremail;
  QString id;
 */


QiwiPostPackageTableModel::QiwiPostPackageTableModel(QObject *parent)
  : QAbstractTableModel(parent) {
  columns.append(trUtf8("PackCode"));
  columns.append(trUtf8("PackSize"));
  columns.append(trUtf8("AmountCharged"));
  columns.append(trUtf8("CalculatedChargeAmount"));
  columns.append(trUtf8("PaymentStatus"));
  columns.append(trUtf8("CreationDate"));
  columns.append(trUtf8("LabelCreationDate"));
  columns.append(trUtf8("Status"));
  columns.append(trUtf8("ConfirmPrinted"));
  columns.append(trUtf8("LabelPrinted"));
  columns.append(trUtf8("BoxMachine"));
  columns.append(trUtf8("AltBoxMachine"));
  columns.append(trUtf8("ReceiverMail"));
  columns.append(trUtf8("Id"));
}

QiwiPostPackageTableModel::~QiwiPostPackageTableModel() {
}

QModelIndex
QiwiPostPackageTableModel::index(int row, int column, const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return createIndex(row, column);
}

QModelIndex
QiwiPostPackageTableModel::parent(const QModelIndex &child) const {
  Q_UNUSED(child);
  return QModelIndex();
}

int
QiwiPostPackageTableModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return packages.size();
}

int
QiwiPostPackageTableModel::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return columns.size();
}

QVariant
QiwiPostPackageTableModel::data(const QModelIndex &index, int role) const {
  if ( !index.isValid() )
    return QVariant();
  if (role != Qt::DisplayRole)
    return QVariant();

  if ( role == Qt::DisplayRole ) {
    const Package package = packages.at(index.row());
    const QString column = columns.at(index.column());
    if ( column == trUtf8("PackCode") ) {
      return package.packcode;
    } else if ( column == trUtf8("PackSize") ) {
      return package.packsize;
    } else if ( column == trUtf8("AmountCharged") ) {
      return package.amountCharged;
    } else if ( column == trUtf8("CalculatedChargeAmount") ) {
      return package.calculatedChargeAmount;
    } else if ( column == trUtf8("PaymentStatus") ) {
      return package.paymentStatus;
    } else if ( column == trUtf8("CreationDate") ) {
      return package.creationDate;
    } else if ( column == trUtf8("LabelCreationDate") ) {
      return package.labelCreationDate;
    } else if ( column == trUtf8("Status") ) {
      return package.status;
    } else if ( column == trUtf8("ConfirmPrinted") ) {
      return package.isConfPrinted;
    } else if ( column == trUtf8("LabelPrinted") ) {
      return package.labelPrinted;
    } else if ( column == trUtf8("BoxMachine") ) {
      return package.preferedBoxMachineName;
    } else if ( column == trUtf8("AltBoxMachine") ) {
      return package.alternativeBoxMachineName;
    } else if ( column == trUtf8("ReceiverMail") ) {
      return package.receiveremail;
    } else if ( column == trUtf8("Id") ) {
      return package.id;
    }
    return QVariant();
  }
  return QVariant();
}

QVariant
QiwiPostPackageTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    static QIcon created(QPixmap(":/internal/images/16x16/basket.png"));
    static QIcon expired(QPixmap(":/internal/images/16x16/basket_error.png"));
    static QIcon returned(QPixmap(":/internal/images/16x16/basket_delete.png"));
    static QIcon delivered(QPixmap(":/internal/images/16x16/basket_go.png"));
    if (role == Qt::DisplayRole) {
      if ( orientation == Qt::Vertical ) {
        return QVariant();
      }
      return columns.at(section);
    }
    if (role == Qt::DecorationRole) {
      if ( orientation == Qt::Vertical ) {
        const Package package = packages.at(section);
        if ( package.status == "Expired" ) {
          return expired;
        } else if ( package.status == "ReturnedTosender" ) {
          return returned;
        } else if ( package.status == "Delivered" ) {
          return delivered;
        } else
          return created;
      }
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}

Qt::ItemFlags
QiwiPostPackageTableModel::flags(const QModelIndex &index) const {
    if ( !index.isValid() )
        return 0;
    return (Qt::ItemIsDragEnabled | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
}

void
QiwiPostPackageTableModel::load(const PackageList &list) {
  beginResetModel();
  packages.clear();
  packages.append(list);
  endResetModel();
}

const Package
QiwiPostPackageTableModel::rowAt(int index) const {
  return packages.at(index);
}
