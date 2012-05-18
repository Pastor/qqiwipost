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

QiwiGuiModel::QiwiGuiModel(QObject *parent) :
  QObject(parent) {
}

QiwiPostMachineTableModel::QiwiPostMachineTableModel(QObject *parent)
  : QAbstractTableModel(parent), iconProvider(new QFileIconProvider) {
//  columns.append(trUtf8("name"));
  columns.append(trUtf8("town"));
  columns.append(trUtf8("postcode"));
  columns.append(trUtf8("street"));
  columns.append(trUtf8("buildingNumber"));

//  columns.append(trUtf8("latitude"));
//  columns.append(trUtf8("longitude"));
//  columns.append(trUtf8("locationDesc"));
//  columns.append(trUtf8("province"));
//  columns.append(trUtf8("status"));
//  columns.append(trUtf8("operatinghours"));
}

QiwiPostMachineTableModel::~QiwiPostMachineTableModel() {
  delete iconProvider;
}

QModelIndex
QiwiPostMachineTableModel::index(int row, int column, const QModelIndex &parent) const {
  return createIndex(row, column);
}

QModelIndex
QiwiPostMachineTableModel::parent(const QModelIndex &child) const {
  return QModelIndex();
}

int
QiwiPostMachineTableModel::rowCount(const QModelIndex &parent) const {
  return machines.size();
}

int
QiwiPostMachineTableModel::columnCount(const QModelIndex &parent) const {
  return columns.size();
}

QVariant
QiwiPostMachineTableModel::data(const QModelIndex &index, int role) const {
  if ( !index.isValid() )
    return QVariant();
  if (role != Qt::DisplayRole)
    return QVariant();
  if ( role == Qt::DecorationRole ) {
    if ( index.column() == 0 )
      return iconProvider->icon(QFileIconProvider::Folder);
    return iconProvider->icon(QFileIconProvider::File);
  }
  if ( role == Qt::DisplayRole ) {
    const Machine machine = machines.at(index.row());
    const QString column = columns.at(index.column());
    if ( column == trUtf8("name") ) {
      return machine.name;
    } else if ( column == trUtf8("postcode") ) {
      return machine.postcode;
    } else if ( column == trUtf8("street") ) {
      return machine.street;
    } else if ( column == trUtf8("buildingNumber") ) {
      return machine.buildingNumber;
    } else if ( column == trUtf8("town") ) {
      return machine.town;
    } else if ( column == trUtf8("latitude") ) {
      return machine.latitude;
    } else if ( column == trUtf8("longitude") ) {
      return machine.longitude;
    } else if ( column == trUtf8("locationDesc") ) {
      return machine.locationDesc;
    } else if ( column == trUtf8("province") ) {
      return machine.province;
    } else if ( column == trUtf8("status") ) {
      return machine.status;
    } else if ( column == trUtf8("operatinghours") ) {
      return machine.operatinghours;
    }
    return QVariant();
  }
  return QVariant();
}

QVariant
QiwiPostMachineTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    static QIcon services(QPixmap(":/images/services.png"));
    if (role == Qt::DisplayRole) {
      if ( orientation == Qt::Vertical )
        return QString::number(section);
      return columns.at(section);
    }
    if (role == Qt::DecorationRole)
      return qVariantFromValue(services);
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
