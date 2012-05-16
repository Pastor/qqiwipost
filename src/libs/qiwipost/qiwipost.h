#ifndef QIWIPOST_H
#define QIWIPOST_H
#include <QObject>
#include "dao.h"
#include "qiwipost_global.h"

namespace Qiwi {
namespace Internal {
  class QiwiPostPrivate;
}
using namespace Internal;

class QIWIPOSTSHARED_EXPORT QiwiPost: public QObject {
  Q_OBJECT
public:
  QiwiPost(QObject *parent = 0);
  virtual ~QiwiPost();

  void loadSettings(const QString &filename);
  void saveSettings();
  void dumpSettings();
  void applaySettings();
  const QString getProperty(const QString &name) const;
  void putProperty(const QString &name, const QString &value);

  const MachineList loadMachines(Error &error);
  const MachineList loadMachinesByName(const QString &name, Error &error);
  const MachineList loadMachinesByPoint(const QString &postCode, Error &error);
  const MachineList loadMachinesByStation(const QString &station, const QString &town, Error &error);

  const QByteArray  loadLabel(const QString &packcode, Error &error, const QString &type = QString());

  const QString loadPackageStatus(const QString &packcode, Error &error);
  const PackageCollection loadPackages(Error &error,
                                 const QString &status = QString(),
                                 const QString &startDate = QString(),
                                 const QString &endDate = QString(),
                                 const QString &isConfPrinted = QString());

  bool hasError() const;

  const QString &errorString() const;

private:
  QiwiPostPrivate *d;
};

}

#endif // QIWIPOST_H
