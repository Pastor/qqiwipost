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

  const MachineList       loadMachines(Error &error);
  const MachineList       loadMachinesByName(const QString &name, Error &error);
  const MachineList       loadMachinesByPoint(const QString &postCode, Error &error);
  const MachineList       loadMachinesByStation(const QString &station, const QString &town, Error &error);

  const QByteArray        loadLabel(Error &error, const QString &packcode, const QString &type = QString());
  //const QByteArray        loadLabel(Error &error, const QString &packcode, const QString &customerRef = QString());


  const QString           loadPackageStatus(const QString &packcode, Error &error);
  const PackageCollection loadPackages(Error &error,
                                 const QString &status = QString(),
                                 const QString &startDate = QString(),
                                 const QString &endDate = QString(),
                                 const QString &isConfPrinted = QString());
  const PaymentCollection loadPayments(Error &error,
                                       const QString &startDate = QString(),
                                       const QString &endDate = QString());
  const PackageList       registerPackage(Error &error, const PackageReg &reg);

  bool                    unregisterPackage(Error &error, const QString &packcode);
  const QByteArray        changePackageCustomerRef(Error &error, const QString &packcode, const QString &customerRef);
  bool                    chanchePackageSize(Error &error, const QString &packcode, const QString &packzise);
  const QByteArray        confirmPackages(Error &error, const QStringList &packages, bool testPrint = true);
  bool                    payPackage(Error &error, const QString &packcode);

  const PriceCollection   listPrices(Error &error);

  const StationList       listStations(Error &error, const QString &town);


  const PurchaseList      listInternalPurchases();
  const Purchase          internalPurchases(const QString &id);
  const Purchase          internalPurchasesByCode(const QString &code);
  const Purchase          createPurchase(const Purchase &purchase);
  bool                    assignPurchase(const Purchase &purchase, const QString &packcode);
  bool                    changePurchaseCustomerRef(const Purchase &purchase, const QString &customerRef);
  bool                    removeInternalPurchase(const QString &id);

  bool hasError() const;

  const QString &errorString() const;
public:
  static const char * const QIWIPOST_URL;
  static const char * const QIWIPOST_USERNAME;
  static const char * const QIWIPOST_PASSWORD;
  static const char * const QIWIPOST_VERSION;
  static const char * const QIWIPOST_LANGUAGE;
  static const char * const QIWIPOST_TIMEOUT;
private:
  QiwiPostPrivate *d;
};

}

#endif // QIWIPOST_H
