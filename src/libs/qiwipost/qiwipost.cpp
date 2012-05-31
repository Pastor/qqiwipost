#include <QtCore/QDebug>
#include <QtCore/QMap>
#include <QtCore/QStringList>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include "qiwipost.h"
#include "qiwipostrequester.h"

namespace Qiwi{
namespace Internal {
  typedef QMap<QString, QString> QiwiPostProperties;

  class QiwiPostPrivate {

      ~QiwiPostPrivate();

      bool checkAndCreate();

      void saveProperties();

      QSqlDatabase db;
      QiwiPostProperties props;
      QiwiPostRequester  requester;
  private:
      friend class QiwiPost;
  };

  const QStringList schema = QStringList()
      << "CREATE TABLE `properties`("
         "  `key`   TEXT NOT NULL,"
         "  `value` TEXT DEFAULT NULL,"
         "  PRIMARY KEY(`key`)"
         ")"
      << "INSERT INTO `properties`(`key`, `value`)"
         "  VALUES('qiwi.url', 'http://apitest.qiwipost.ru/')"
      << "INSERT INTO `properties`(`key`, `value`)"
         "  VALUES('qiwi.username', '8880000000')"
      << "INSERT INTO `properties`(`key`, `value`)"
         "  VALUES('qiwi.password', '9876543210')"
      << "INSERT INTO `properties`(`key`, `value`)"
         "  VALUES('qiwi.proto.version', '1.2')"
      << "INSERT INTO `properties`(`key`, `value`)"
         "  VALUES('qiwi.language', 'RU')"
      << "INSERT INTO `properties`(`key`, `value`)"
         "  VALUES('qiwi.timeout', '20000')"
      << "CREATE TABLE `purchase`("
         "  `fname`  TEXT DEFAULT NULL,"
         "  `sname`  TEXT DEFAULT NULL,"
         "  `phone`  TEXT NOT NULL,"
         "  `code`   TEXT DEFAULT NULL,"
         "  `customerRef`  TEXT DEFAULT NULL"
         ")";
}
}

using namespace Qiwi;
using namespace Qiwi::Internal;

/** class QiwiPostPrivate*/
bool
QiwiPostPrivate::checkAndCreate() {
  QSqlQuery q(db);
  if ( q.exec("SELECT * FROM properties") ) {
    return true;
  }
  QStringListIterator it(schema);
  while ( it.hasNext() ) {
    if (!q.exec(it.next())) {
      qDebug() << q.lastError().text();
      return false;
    }
  }
  return true;
}

void
QiwiPostPrivate::saveProperties() {
  QSqlQuery q(db);

  q.exec("DELETE FROM `properties`");
  if ( q.prepare("INSERT INTO `properties`(`key`, `value`) VALUES(:key, :value)") ) {
    QMapIterator<QString, QString> it(props);
    while ( it.hasNext() ) {
      it.next();

      q.bindValue(":key", it.key());
      q.bindValue(":value", it.value());
      if (!q.exec())
        qDebug() << q.lastError().text();
    }
  } else {
    qDebug() << q.lastError().text();
  }
}

QiwiPostPrivate::~QiwiPostPrivate() {
  db.close();
}

/** class QiwiPost */
const char * const QiwiPost::QIWIPOST_URL = "qiwi.url";
const char * const QiwiPost::QIWIPOST_USERNAME = "qiwi.username";
const char * const QiwiPost::QIWIPOST_PASSWORD = "qiwi.password";
const char * const QiwiPost::QIWIPOST_VERSION  = "qiwi.version";
const char * const QiwiPost::QIWIPOST_LANGUAGE = "qiwi.language";
const char * const QiwiPost::QIWIPOST_TIMEOUT  = "qiwi.timeout";


QiwiPost::QiwiPost(QObject *parent)
  : QObject(parent), d(new QiwiPostPrivate){
}

QiwiPost::~QiwiPost() {
  delete d;
}

void
QiwiPost::loadSettings(const QString &filename) {
  d->db = QSqlDatabase::addDatabase("QSQLITE");
  d->db.setDatabaseName(filename);
  if (!d->db.open()) {
    qDebug() << d->db.lastError().text();
    return;
  }
  d->checkAndCreate();
  QSqlQuery query(d->db);
  if ( query.exec("SELECT key, value FROM properties") ) {
    while ( query.next() ) {
      QString key = query.value(0).toString();
      QString value = query.value(1).toString();
      d->props.insert(key, value);
    }
  } else {
    qDebug() << query.lastError().text();
  }
}

void
QiwiPost::applaySettings() {
  QString username = d->props[QIWIPOST_USERNAME];
  if ( username == 0 || username.isEmpty() ) {
    qDebug() << "Username not set";
    return;
  }
  QString password = d->props[QIWIPOST_PASSWORD];
  if ( password == 0 || password.isEmpty() ) {
    qDebug() << "Password not set";
    return;
  }
  QString url = d->props[QIWIPOST_URL];
  if ( url == 0 || url.isEmpty() ) {
    qDebug() << "Url not set";
    return;
  }
  quint64 timeout = d->props[QIWIPOST_TIMEOUT].toInt();
  d->requester.setTimeout(timeout);
  d->requester.setUsername(username);
  d->requester.setPassword(password);
  d->requester.setUrl(url);
}

void
QiwiPost::saveSettings() {
  d->saveProperties();
}

void
QiwiPost::dumpSettings() {
  QSqlQuery q(d->db);

  q.exec("SELECT `uid`, `key`, `value` FROM `properties`");
  while ( q.next() ) {
    qDebug() << q.value(0) << q.value(1) << q.value(2);
  }
}

const QString
QiwiPost::getProperty(const QString &name) const {
  return d->props[name];
}

void
QiwiPost::putProperty(const QString &name, const QString &value) {
  d->props[name] = value;
}

const MachineList
QiwiPost::loadMachines(Error &error) {
  QueryParams params;
  d->requester.request("listmachines_xml", params, params);
  d->requester.wait();
  if ( hasError() ) {
    qDebug() << errorString();
    return MachineList();
  } else if ( d->requester.isTimeout() ) {
    error.desc = QObject::trUtf8("Timeout");
    error.hasError = true;
    return MachineList();
  }
  return Machine::parseList(d->requester.result(), error);
}

const MachineList
QiwiPost::loadMachinesByPoint(const QString &postCode, Error &error) {
  QueryParams gp;
  QueryParams pp;

  gp.insert("postcode", postCode.toLocal8Bit());
  d->requester.request("findnearestmachinesbypostcode", gp, pp);
  d->requester.wait();
  if ( hasError() ) {
    qDebug() << errorString();
    return MachineList();
  } else if ( d->requester.isTimeout() ) {
    error.desc = QObject::trUtf8("Timeout");
    error.hasError = true;
    return MachineList();
  }
  return Machine::parseList(d->requester.result(), error);
}

const MachineList
QiwiPost::loadMachinesByStation(const QString &station, const QString &town, Error &error) {
  QueryParams gp;
  QueryParams pp;

  gp.insert("stationname", station.toLocal8Bit());
  gp.insert("town", town.toLocal8Bit());
  d->requester.request("findnearestmachinesbymetrostation", gp, pp);
  d->requester.wait();
  if ( hasError() ) {
    qDebug() << errorString();
    return MachineList();
  } else if ( d->requester.isTimeout() ) {
    error.desc = QObject::trUtf8("Timeout");
    error.hasError = true;
    return MachineList();
  }
  return Machine::parseList(d->requester.result(), error);
}

const MachineList
QiwiPost::loadMachinesByName(const QString &name, Error &error) {
  QueryParams gp;
  QueryParams pp;

  gp.insert("name", name.toLocal8Bit());
  d->requester.request("findnebyname", gp, pp);
  d->requester.wait();
  if ( hasError() ) {
    qDebug() << errorString();
    return MachineList();
  } else if ( d->requester.isTimeout() ) {
    error.desc = QObject::trUtf8("Timeout");
    error.hasError = true;
    return MachineList();
  }
  return Machine::parseList(d->requester.result(), error);
}

const QByteArray
QiwiPost::loadLabel(Error &error, const QString &packcode, const QString &type) {
  QueryParams gp;
  QueryParams pp;

  //qDebug() << packcode.toUtf8();
  pp.insert("packcode", packcode.toUtf8());
  pp.insert("labelType", type.toUtf8());
  d->requester.request("getsticker", gp, pp);
  d->requester.wait();
  if ( hasError() ) {
    qDebug() << errorString();
    return QByteArray();
  } else if ( d->requester.isTimeout() ) {
    error.desc = QObject::trUtf8("Timeout");
    error.hasError = true;
    return QByteArray();
  }
  QByteArray data = d->requester.result();
  if ( error.load(data) )
    return QByteArray();
  return data;
}

//const QByteArray
//QiwiPost::loadLabel(Error &error, const QString &packcode, const QString &customerRef) {
//  QueryParams gp;
//  QueryParams pp;

//  pp.insert("packcode", packcode.toLocal8Bit());
//  pp.insert("customerRef", customerRef.toLocal8Bit());
//  d->requester.request("setcustomerref", gp, pp);
//  d->requester.wait();
//  if ( hasError() ) {
//    qDebug() << errorString();
//    return QByteArray();
//  } else if ( d->requester.isTimeout() ) {
//    error.desc = QObject::trUtf8("Timeout");
//    error.hasError = true;
//    return QByteArray();
//  }
//  QByteArray data = d->requester.result();
//  if ( error.load(data) )
//    return QByteArray();
//  return data;
//}

const QString
QiwiPost::loadPackageStatus(const QString &packcode, Error &error) {
  QueryParams gp;
  QueryParams pp;

  if ( !packcode.isEmpty() )
    gp.insert("packcode", packcode.toLocal8Bit());
  d->requester.request("getpackstatus", gp, pp);
  d->requester.wait();
  if ( hasError() ) {
    qDebug() << errorString();
    return QByteArray();
  } else if ( d->requester.isTimeout() ) {
    error.desc = QObject::trUtf8("Timeout");
    error.hasError = true;
    return "";
  }
  Status status;
  status.load(d->requester.result(), error);
  return status.status;
}

const PackageCollection
QiwiPost::loadPackages(Error &error,
                       const QString &status,
                       const QString &startDate,
                       const QString &endDate,
                       const QString &isConfPrinted) {
  QueryParams gp;
  QueryParams pp;

  if ( !status.isEmpty() )
    pp.insert("status", status.toLocal8Bit());
  if ( !startDate.isEmpty() )
    pp.insert("startdate", startDate.toLocal8Bit());
  if ( !endDate.isEmpty() )
    pp.insert("enddate", endDate.toLocal8Bit());
  if ( !isConfPrinted.isEmpty() )
    pp.insert("is_conf_printed", isConfPrinted.toLocal8Bit());
  d->requester.request("getpacksbysender", gp, pp);
  d->requester.wait();
  if ( hasError() ) {
    qDebug() << errorString();
    return PackageCollection();
  } else if ( d->requester.isTimeout() ) {
    error.desc = QObject::trUtf8("Timeout");
    error.hasError = true;
    return PackageCollection();
  }
  return Package::parseList(d->requester.result(), error);
}

const PaymentCollection
QiwiPost::loadPayments(Error &error,
                       const QString &startDate,
                       const QString &endDate) {
  QueryParams gp;
  QueryParams pp;

  if ( !startDate.isEmpty() )
    pp.insert("startdate", startDate.toLocal8Bit());
  if ( !endDate.isEmpty() )
    pp.insert("enddate", endDate.toLocal8Bit());
  d->requester.request("getcodreport", gp, pp);
  d->requester.wait();
  if ( hasError() ) {
    qDebug() << errorString();
    return PaymentCollection();
  } else if ( d->requester.isTimeout() ) {
    error.desc = QObject::trUtf8("Timeout");
    error.hasError = true;
    return PaymentCollection();
  }
  return Payment::parseList(d->requester.result(), error);
}

const PackageList
QiwiPost::registerPackage(Error &error, const PackageReg &reg) {
  QueryParams gp;
  QueryParams pp;

  pp.insert("content", PackageReg::toXml(PackageRegList() << reg, false).toUtf8());
  d->requester.request("createdeliverypacks", gp, pp);
  d->requester.wait();
  if ( hasError() ) {
    qDebug() << errorString();
    return PackageList();
  } else if ( d->requester.isTimeout() ) {
    error.desc = QObject::trUtf8("Timeout");
    error.hasError = true;
    return PackageList();
  }
  return Package::parseList( d->requester.result(), error ).packages;
}

bool
QiwiPost::unregisterPackage(Error &error, const QString &packcode) {
  QueryParams gp;
  QueryParams pp;

  pp.insert("packcode", packcode.toLocal8Bit());
  d->requester.request("cancelpack", gp, pp);
  d->requester.wait();
  QByteArray data = d->requester.result();
  if ( hasError() ) {
    qDebug() << errorString();
    return false;
  } else if ( d->requester.isTimeout() ) {
    error.desc = QObject::trUtf8("Timeout");
    error.hasError = true;
    return false;
  } else if ( error.load(data) ) {
    return false;
  }
  return data.toInt() == 1;
}

bool
QiwiPost::chanchePackageSize(Error &error, const QString &packcode, const QString &packsize) {
  QueryParams gp;
  QueryParams pp;

  pp.insert("packcode", packcode.toLocal8Bit());
  pp.insert("packsize", packsize.toLocal8Bit());
  d->requester.request("change_packsize", gp, pp);
  d->requester.wait();
  QByteArray data = d->requester.result();
  if ( hasError() ) {
    qDebug() << errorString();
    return false;
  } else if ( d->requester.isTimeout() ) {
    error.desc = QObject::trUtf8("Timeout");
    error.hasError = true;
    return false;
  } else if ( error.load(data) ) {
    return false;
  }
  return data.toInt() == 1;
}

const QByteArray
QiwiPost::changePackageCustomerRef(Error &error, const QString &packcode, const QString &customerRef) {
  QueryParams gp;
  QueryParams pp;

  pp.insert("packcode", packcode.toUtf8());
  pp.insert("customerRef", customerRef.toUtf8());
  d->requester.request("setcustomerref", gp, pp);
  d->requester.wait();
  QByteArray data = d->requester.result();
  if ( hasError() ) {
    qDebug() << errorString();
    return false;
  } else if ( d->requester.isTimeout() ) {
    error.desc = QObject::trUtf8("Timeout");
    error.hasError = true;
    return QByteArray();
  } else if ( error.load(data) ) {
    return QByteArray();
  }
  return data;
}

bool
QiwiPost::payPackage(Error &error, const QString &packcode) {
  QueryParams gp;
  QueryParams pp;

  pp.insert("packcode", packcode.toUtf8());
  d->requester.request("payforpack", gp, pp);
  d->requester.wait();
  QByteArray data = d->requester.result();
  if ( hasError() ) {
    qDebug() << errorString();
    return false;
  } else if ( d->requester.isTimeout() ) {
    error.desc = QObject::trUtf8("Timeout");
    error.hasError = true;
    return false;
  } else if ( error.load(data) ) {
    return false;
  }
  return data.toInt() == 1;
}

const QByteArray
QiwiPost::confirmPackages(Error &error, const QStringList &packages, bool testPrint) {
  QueryParams gp;
  QueryParams pp;

  const QString confirmContent = PackageReg::toXml(packages, testPrint);
  //qDebug() << confirmContent;
  pp.insert("content", confirmContent.toUtf8());
  d->requester.request("getconfirmprintout", gp, pp);
  d->requester.wait();
  QByteArray data = d->requester.result();
  if ( hasError() ) {
    qDebug() << errorString();
    return QByteArray();
  } else if ( d->requester.isTimeout() ) {
    error.desc = QObject::trUtf8("Timeout");
    error.hasError = true;
    return QByteArray();
  } else if ( error.load(data) ) {
    return QByteArray();
  }
  return data;
}

const PriceCollection
QiwiPost::listPrices(Error &error) {
  QueryParams gp;
  QueryParams pp;

  d->requester.request("pricelist", gp, pp);
  d->requester.wait();
  if ( hasError() ) {
    qDebug() << errorString();
    return PriceCollection();
  } else if ( d->requester.isTimeout() ) {
    error.desc = QObject::trUtf8("Timeout");
    error.hasError = true;
    return PriceCollection();
  }
  return Price::parseList(d->requester.result(), error);
}

const StationList
QiwiPost::listStations(Error &error, const QString &town) {
  QueryParams gp;
  QueryParams pp;

  gp.insert("town", town.toUtf8());
  d->requester.request("getallmetrostations", gp, pp);
  d->requester.wait();
  if ( hasError() ) {
    qDebug() << errorString();
    return StationList();
  } else if ( d->requester.isTimeout() ) {
    error.desc = QObject::trUtf8("Timeout");
    error.hasError = true;
    return StationList();
  }
  return Station::parseList(d->requester.result(), error);
}

const PurchaseList
QiwiPost::listInternalPurchases() {
  QSqlQuery q(d->db);
  PurchaseList result;

  if ( !q.exec("SELECT `uid`, `fname`, `sname`, `phone`, `code` FROM `purchase`") ) {
    qDebug() << q.lastError().text();
    return result;
  }
  while ( q.next() ) {
    Purchase purchase;
    purchase.id = q.value(0).toString();
    purchase.fname = q.value(1).toString();
    purchase.sname = q.value(2).toString();
    purchase.phone = q.value(3).toString();
    purchase.code = q.value(4).toString();
    result << purchase;
  }
  return result;
}

const Purchase
QiwiPost::internalPurchases(const QString &id) {
  QSqlQuery q(d->db);
  Purchase result;

  if ( !q.prepare("SELECT rowid, `fname`, `sname`, `phone`, `code` FROM `purchase` WHERE rowid = :uid") ) {
    qDebug() << q.lastError().text();
    return result;
  }
  q.bindValue(":uid", id);
  if ( !q.exec() ) {
    qDebug() << q.lastError().text();
    return result;
  }
  if ( q.next() ) {
    result.id    = q.value(0).toString();
    result.fname = q.value(1).toString();
    result.sname = q.value(2).toString();
    result.phone = q.value(3).toString();
    result.code  = q.value(4).toString();
  }
  return result;
}

const Purchase
QiwiPost::internalPurchasesByCode(const QString &code) {
  QSqlQuery q(d->db);
  Purchase result;

  if ( !q.prepare("SELECT rowid, `fname`, `sname`, `phone`, `code`, `customerRef` FROM `purchase` WHERE `code` = :code") ) {
    qDebug() << q.lastError().text();
    return result;
  }
  q.bindValue(":code", code);
  if ( !q.exec() ) {
    qDebug() << q.lastError().text();
    return result;
  }
  if ( q.next() ) {
    result.id    = q.value(0).toString();
    result.fname = q.value(1).toString();
    result.sname = q.value(2).toString();
    result.phone = q.value(3).toString();
    result.code  = q.value(4).toString();
    result.customerRef  = q.value(5).toString();
  }
  return result;
}

bool
QiwiPost::removeInternalPurchase(const QString &id) {
  QSqlQuery q(d->db);
  if ( !q.prepare("DELETE FROM `purchase` WHERE rowid = :uid") ) {
    qDebug() << q.lastError().text();
    return false;
  }
  q.bindValue(":uid", id);
  return q.exec();
}

const Purchase
QiwiPost::createPurchase(const Purchase &purchase) {
  Purchase result(purchase);
  QSqlQuery q(d->db);

  if ( !q.prepare("INSERT INTO `purchase`(`fname`, `sname`, `phone`, `customerRef`) "
                  "VALUES(:fname, :sname, :phone, :customerRef)") ) {
    result.error = q.lastError().text();
    qDebug() << q.lastError().text();
    return result;
  }
  q.bindValue(":fname", purchase.fname);
  q.bindValue(":sname", purchase.sname);
  q.bindValue(":phone", purchase.phone);
  q.bindValue(":customerRef", purchase.customerRef);
  if ( !q.exec() ) {
    result.error = q.lastError().text();
    qDebug() << q.lastError().text();
    return result;
  }
  result.id = q.lastInsertId().toString();
  return result;
}

bool
QiwiPost::assignPurchase(const Purchase &purchase, const QString &packcode) {
  QSqlQuery q(d->db);

  if ( !q.prepare("UPDATE `purchase` SET `code` = :code WHERE rowid = :uid") ) {
    qDebug() << q.lastError().text();
    return false;
  }
  q.bindValue(":code", packcode);
  q.bindValue(":uid", purchase.id);
  if ( !q.exec() ) {
    qDebug() << q.lastError().text();
    return false;
  }
  return true;
}

bool
QiwiPost::changePurchaseCustomerRef(const Purchase &purchase, const QString &customerRef) {
  QSqlQuery q(d->db);

  if ( !q.prepare("UPDATE `purchase` SET `customerRef` = :customerRef WHERE rowid = :uid") ) {
    qDebug() << q.lastError().text();
    return false;
  }
  q.bindValue(":customerRef", customerRef);
  q.bindValue(":uid", purchase.id);
  if ( !q.exec() ) {
    qDebug() << q.lastError().text();
    return false;
  }
  return true;
}

bool
QiwiPost::hasError() const {
  return d->requester.hasError();
}

const QString &
QiwiPost::errorString() const {
  return d->requester.errorString();
}


