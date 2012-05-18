#ifndef QIWIGUIMODEL_H
#define QIWIGUIMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QTableWidget>
#include <QFileIconProvider>
#include <qiwipost/dao.h>
#include "qiwigui_global.h"

class QTableWidget;
namespace Qiwi {

class QiwiGuiModel : public QObject {
  Q_OBJECT
public:
  QiwiGuiModel(QObject *parent = 0);
};

class QIWIGUISHARED_EXPORT QiwiPostMachineTableModel: public QAbstractTableModel {
  Q_OBJECT
public:
  QiwiPostMachineTableModel(QObject *parent = 0);
  virtual ~QiwiPostMachineTableModel();

  virtual QModelIndex index(int row, int column,
                            const QModelIndex &parent = QModelIndex()) const;
  virtual QModelIndex parent(const QModelIndex &child) const;
  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
  virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;

  void load(const MachineList &list);
  const Machine rowAt(int index) const;
private:
  MachineList        machines;
  QStringList        columns;
};

class QIWIGUISHARED_EXPORT QiwiPostPackageTableModel: public QAbstractTableModel {
  Q_OBJECT
public:
  QiwiPostPackageTableModel(QObject *parent = 0);
  virtual ~QiwiPostPackageTableModel();

  virtual QModelIndex index(int row, int column,
                            const QModelIndex &parent = QModelIndex()) const;
  virtual QModelIndex parent(const QModelIndex &child) const;
  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
  virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;

  void load(const PackageList &list);
  const Package rowAt(int index) const;
private:
  PackageList        packages;
  QStringList        columns;
};

}

#endif // QIWIGUIMODEL_H
