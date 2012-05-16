#ifndef DAO_H
#define DAO_H
#include <QObject>
#include <QList>
#include <QMetaType>
#include "qiwipost_global.h"

namespace Qiwi {

struct QIWIPOSTSHARED_EXPORT Machine {
  QString name;
  QString postcode;
  QString street;
  QString buildingNumber;
  QString town;
  QString latitude;
  QString longitude;
  QString locationDesc;

  Machine()
  {}

  Machine(const Machine &other)
    : name(other.name), postcode(other.postcode),
      street(other.street), buildingNumber(other.buildingNumber),
      town(other.town), latitude(other.latitude),
      longitude(other.longitude), locationDesc(other.locationDesc)
  {}
};
typedef QList<Machine>             MachineList;
typedef QListIterator<Machine>     MachineListIterator;

struct QIWIPOSTSHARED_EXPORT Package {
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

  Package()
  {}

  Package(const Package &other)
    : packcode(other.packcode), packsize(other.packsize),
      amountCharged(other.amountCharged),
      calculatedChargeAmount(other.calculatedChargeAmount),
      paymentStatus(other.paymentStatus), creationDate(other.creationDate),
      labelCreationDate(other.labelCreationDate), status(other.status),
      isConfPrinted(other.isConfPrinted), labelPrinted(other.labelPrinted),
      onDeliveryAmount(other.onDeliveryAmount),
      preferedBoxMachineName(other.preferedBoxMachineName),
      alternativeBoxMachineName(other.alternativeBoxMachineName)
  {}

};
typedef QList<Package>             PackageList;
typedef QListIterator<Package>     PackageListIterator;

struct QIWIPOSTSHARED_EXPORT Payment {
  QString amount;
  QString posdesc;
  QString packcode;
  QString transactionDate;

  Payment()
  {}

  Payment(const Payment &other)
    : amount(other.amount), posdesc(other.posdesc),
      packcode(other.packcode), transactionDate(other.transactionDate)
  {}
};
typedef QList<Payment>             PaymentList;
typedef QListIterator<Payment>     PaymentListIterator;


struct PackageReg;
typedef QList<PackageReg>             PackageRegList;
typedef QListIterator<PackageReg>     PackageRegListIterator;

struct QIWIPOSTSHARED_EXPORT PackageReg {
  QString id;
  QString addressPhoneNumber;
  QString senderPhoneNumber;
  QString boxMachineName;
  QString packType;
  QString onDeliveryAmount;
  QString customerRef;

  PackageReg()
  {}

  PackageReg(const PackageReg &other)
    : id(other.id), addressPhoneNumber(other.addressPhoneNumber),
      senderPhoneNumber(other.senderPhoneNumber), boxMachineName(other.boxMachineName),
      packType(other.packType), onDeliveryAmount(other.onDeliveryAmount),
      customerRef(other.customerRef)
  {}

  const QString toXml(int tab = 2) const;

  static const QString toXml(const PackageRegList &list, bool autoLabel = true, int tab = 2);

};

struct QIWIPOSTSHARED_EXPORT PackType {
  QString type;
  QString price;

  PackType()
  {}

  PackType(const PackType &other)
    : type(other.type), price(other.price)
  {}
};
typedef QList<PackType>             PackTypeList;
typedef QListIterator<PackType>     PackTypeListIterator;

struct QIWIPOSTSHARED_EXPORT Station {
  QString metroStationName;
  QString town;
  QString latitude;
  QString longitude;

  Station()
  {}

  Station(const Station &other)
    : metroStationName(other.metroStationName), town(other.town),
      latitude(other.latitude), longitude(other.longitude)
  {}

};
typedef QList<Station>             StationList;
typedef QListIterator<Station>     StationListIterator;

}

Q_DECLARE_METATYPE(Qiwi::Machine)
Q_DECLARE_METATYPE(Qiwi::Package)
Q_DECLARE_METATYPE(Qiwi::PackageReg)
Q_DECLARE_METATYPE(Qiwi::Payment)
Q_DECLARE_METATYPE(Qiwi::PackType)
Q_DECLARE_METATYPE(Qiwi::Station)

#endif // DAO_H