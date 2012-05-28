#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QTextStream>
#include <QStringList>
#include "dao.h"

namespace Qiwi {
namespace Internal {
  static inline void
  private_writeElement(QXmlStreamWriter &writer, QString elementName, QString elementValue) {
    writer.writeTextElement(elementName, elementValue);
  }



  static const char * const START = "paczkomaty";
  static const char * const ERROR = "error";
  static const char * const CUSTOMER = "customer";
  static const char * const STATUS = "status";
  static const char * const KEY = "key";
  static const char * const MACHINE = "machine";
  static const char * const CITYGROUP = "citygroup";
  static const char * const NAME = "name";
  static const char * const PROVINCE = "province";
  static const char * const POSTCODE = "postcode";
  static const char * const STREET = "street";
  static const char * const BUILDINGNUMBER = "buildingnumber";
  static const char * const TOWN = "town";
  static const char * const LATITUDE = "latitude";
  static const char * const LONGITUDE = "longitude";
  static const char * const OPERATINGHOURS = "operatinghours";
  static const char * const LOCATIONDESCRIPTION = "locationdescription";

  static const char * const PACK = "pack";
  static const char * const STARTDATE = "startdate";
  static const char * const ENDDATE = "enddate";
  static const char * const RESULTS = "results";
  static const char * const PACKCODE = "packcode";
  static const char * const PACKSIZE = "packsize";
  static const char * const AMOUNTCHARGED = "amountcharged";
  static const char * const CALCULATEDCHARGEAMOUNT = "calculatedchargeamount";
  static const char * const PAYMENTSTATUS = "paymentstatus";
  static const char * const CREATIONDATE = "creationdate";
  static const char * const LABELCREATIONDATE = "labelcreationdate";
  static const char * const ISCONFPRINTED = "is_conf_printed";
  static const char * const LABELPRINTED = "labelprinted";
  static const char * const ONDELIVERYAMOUNT = "ondeliveryamount";
  static const char * const PREFEREDBOXMACHINENAME = "preferedboxmachinename";
  static const char * const ALTERNATIVEBOXMACHINENAME = "alternativeboxmachinename";
  static const char * const RECEIVERAMAIL = "receiveremail";

  static const char * const PAYMENT = "payment";
  static const char * const POSDESC = "posdesc";
  static const char * const AMOUNT = "amount";
  static const char * const TRANSACTIONDATE = "transactiondate";
  static const char * const BOXMACHINENAME = "boxmachinename";
  static const char * const COMISSIONFORCOD = "comissionforcod";
  static const char * const DATEOFPARCELDELIVERED = "dateofparceldelivered";
  static const char * const ID = "id";
  static const char * const PARCELBARCODE = "parcelbarcode";
  static const char * const PRICEFORDELIVERY = "pricefordelivery";
  static const char * const RECEIVEDCOD = "receivedcod";

  static const char * const TYPE = "type";
  static const char * const PRICE = "price";
  static const char * const PACKTYPE = "packtype";
  static const char * const ONDELIVERYPAYMENT = "on_delivery_payment";

  static const char * const STATION = "station";
  static const char * const METROSTATIONSNAME = "metrostationsname";
}
}

using namespace Qiwi;
using namespace Qiwi::Internal;

/** struct Error*/
bool
Error::load(const QByteArray &data) {
  QXmlStreamReader reader(data);
  while (!reader.atEnd()) {
    reader.readNext();
    switch ( reader.tokenType() ) {
    case QXmlStreamReader::StartElement: {
      QString element = reader.name().toString();
      if ( element == START ) {
          //ignore
      } else if ( element == CUSTOMER ) {
          //ignore
      } else if ( element == ERROR ) {
        key = reader.attributes().value(KEY).toString();
        desc = reader.readElementText().trimmed();
        hasError = true;
        return true;
      }
      break;
    }
    case QXmlStreamReader::EndElement:
    case QXmlStreamReader::EndDocument:
    case QXmlStreamReader::Comment:
    case QXmlStreamReader::Characters:
      break;
    default:
      break;
    }
  }
  return false;
}

/** struct Price */
void
Price::load(QXmlStreamReader &reader) {
  QString element = reader.name().toString();
  if ( element != PACKTYPE ) {
    reader.raiseError("Illegal tag name");
    return;
  }
  while (!reader.atEnd()) {
    reader.readNext();
    switch ( reader.tokenType() ) {
    case QXmlStreamReader::StartElement: {
      element = reader.name().toString();
      if ( element == TYPE ) {
        type = reader.readElementText().trimmed();
      } else if ( element == PRICE ) {
        price = reader.readElementText().trimmed();
      }
      break;
    }
    case QXmlStreamReader::EndElement:
    case QXmlStreamReader::EndDocument:
    case QXmlStreamReader::Comment:
    case QXmlStreamReader::Characters:
      break;
    default:
      break;
    }
  }
}

const PriceCollection
Price::parseList(const QByteArray &data, Error &error) {
  PriceList list;
  QString onDeliveryPayment;
  QXmlStreamReader reader(data);
  while (!reader.atEnd()) {
    reader.readNext();
    switch (reader.tokenType()) {
    case QXmlStreamReader::StartElement: {
      QString element = reader.name().toString();
      if ( element == START ) {
        break;
      } else if ( element == PACKTYPE ) {
        Price price;
        price.load(reader);
        list.append(price);
      } else if ( element == ONDELIVERYPAYMENT ) {
        onDeliveryPayment = reader.readElementText().trimmed();
      } else if ( element == ERROR ) {
        error.key = reader.attributes().value(KEY).toString();
        error.desc = reader.readElementText().trimmed();
        error.hasError = true;
      } else {
        reader.raiseError(QString("Invalid element: %1").arg(element));
      }
      break;
    }
    case QXmlStreamReader::EndElement:
    case QXmlStreamReader::EndDocument:
    case QXmlStreamReader::Comment:
    case QXmlStreamReader::Characters:
      break;
    default:
      //reader.raiseError("Unexpected token");
      break;
    }
  }
  if (reader.hasError()) {
    error.internalError = QObject::tr("Error parse data: %2, at line %3, column %4")
                .arg(reader.errorString())
                .arg(reader.lineNumber())
                .arg(reader.columnNumber());
    error.hasError = true;
    error.data = data;
  }
  PriceCollection collection;
  collection.onDeliveryPayment = onDeliveryPayment;
  collection.prices = list;
  return collection;
}

/** struct Status */
void
Status::load(const QByteArray &data, Error &error) {
  QXmlStreamReader reader(data);
  while (!reader.atEnd()) {
    reader.readNext();
    switch ( reader.tokenType() ) {
    case QXmlStreamReader::StartElement: {
      QString element = reader.name().toString();
      if ( element == START ) {
      } else if ( element == STATUS ) {
        status = reader.readElementText().trimmed();
      } else if ( element == ERROR ) {
        error.key = reader.attributes().value(KEY).toString();
        error.desc = reader.readElementText().trimmed();
        error.hasError = true;
      }
      break;
    }
    case QXmlStreamReader::EndElement:
    case QXmlStreamReader::EndDocument:
    case QXmlStreamReader::Comment:
    case QXmlStreamReader::Characters:
      break;
    default:
      break;
    }
  }
}

const QString
Status::desc() const {
  return "";
}

/** struct Machine */
MachineList
Machine::parseList(const QByteArray &data, Error &error) {
  MachineList list;
  QXmlStreamReader reader(data);
  while (!reader.atEnd()) {
    reader.readNext();
    switch (reader.tokenType()) {
    case QXmlStreamReader::StartElement: {
      QString element = reader.name().toString();
      if ( element == START ) {
        break;
      } else if ( element == MACHINE ) {
        Machine machine;
        machine.load(reader);
        list.append(machine);
      } else if ( element == ERROR ) {
        error.key = reader.attributes().value(KEY).toString();
        error.desc = reader.readElementText().trimmed();
      } else {
        reader.raiseError(QString("Invalid element: %1").arg(element));
      }
      break;
    }
    case QXmlStreamReader::EndElement:
    case QXmlStreamReader::EndDocument:
    case QXmlStreamReader::Comment:
    case QXmlStreamReader::Characters:
      break;
    default:
      //reader.raiseError("Unexpected token");
      break;
    }
  }
  if (reader.hasError()) {
      error.internalError = QObject::tr("Error parse data: %2, at line %3, column %4")
                  .arg(reader.errorString())
                  .arg(reader.lineNumber())
                  .arg(reader.columnNumber());
      error.hasError = true;
      error.data = data;
  }
  return list;
}

void
Machine::load(QXmlStreamReader &reader) {
  QString element = reader.name().toString();
  if ( element != MACHINE ) {
    reader.raiseError("Illegal tag name");
    return;
  }
  while ( !reader.atEnd() ) {
    reader.readNext();
    switch ( reader.tokenType() ) {
      case QXmlStreamReader::StartElement: {
        element = reader.name().toString();
        if ( element == NAME ) {
          name = reader.readElementText().trimmed();
        } else if ( element == POSTCODE ) {
          postcode = reader.readElementText().trimmed();
        } else if ( element == STREET ) {
          street = reader.readElementText().trimmed();
        } else if ( element == BUILDINGNUMBER ) {
          buildingNumber = reader.readElementText().trimmed();
        } else if ( element == TOWN ) {
          town = reader.readElementText().trimmed();
        } else if ( element == LATITUDE ) {
          latitude = reader.readElementText().trimmed();
        } else if ( element == LONGITUDE ) {
          longitude = reader.readElementText().trimmed();
        } else if ( element == LOCATIONDESCRIPTION ) {
          locationDesc = reader.readElementText().trimmed();
        } else if ( element == PROVINCE ) {
          province = reader.readElementText().trimmed();
        } else if ( element == STATUS ) {
          status = reader.readElementText().trimmed();
        } else if ( element == OPERATINGHOURS ) {
          operatinghours = reader.readElementText().trimmed();
        } else if ( element == CITYGROUP ) {
          citygroup = reader.readElementText().trimmed();
        } else {
          reader.raiseError(QString("Invalid element: %1").arg(element));
        }
        break;
      }
      case QXmlStreamReader::EndElement: {
        element = reader.name().toString();
        if ( element == MACHINE ) {
          return;
        }
        break;
      }
      case QXmlStreamReader::EndDocument:
      case QXmlStreamReader::Comment:
      case QXmlStreamReader::Characters:
        break;
      default:
        reader.raiseError("Unexpected token");
        break;
    }
  }
}

/** struct Package */
void
Package::load(QXmlStreamReader &reader) {
  QString element = reader.name().toString();
  if ( element != PACK ) {
    reader.raiseError("Illegal tag name");
    return;
  }
  while ( !reader.atEnd() ) {
    reader.readNext();
    switch ( reader.tokenType() ) {
      case QXmlStreamReader::StartElement: {
        element = reader.name().toString();
        if ( element == PACKCODE ) {
          packcode = reader.readElementText().trimmed();
        } else if ( element == PACKSIZE ) {
          packsize = reader.readElementText().trimmed();
        } else if ( element == AMOUNTCHARGED ) {
          amountCharged = reader.readElementText().trimmed();
        } else if ( element == CALCULATEDCHARGEAMOUNT ) {
          calculatedChargeAmount = reader.readElementText().trimmed();
        } else if ( element == PAYMENTSTATUS ) {
          paymentStatus = reader.readElementText().trimmed();
        } else if ( element == CREATIONDATE ) {
          creationDate = reader.readElementText().trimmed();
        } else if ( element == LABELCREATIONDATE ) {
          labelCreationDate = reader.readElementText().trimmed();
        } else if ( element == STATUS ) {
          status = reader.readElementText().trimmed();
        } else if ( element == ISCONFPRINTED ) {
          isConfPrinted = reader.readElementText().trimmed();
        } else if ( element == LABELPRINTED ) {
          labelPrinted = reader.readElementText().trimmed();
        } else if ( element == ONDELIVERYAMOUNT ) {
          onDeliveryAmount = reader.readElementText().trimmed();
        } else if ( element == PREFEREDBOXMACHINENAME ) {
          preferedBoxMachineName = reader.readElementText().trimmed();
        } else if ( element == ALTERNATIVEBOXMACHINENAME ) {
          alternativeBoxMachineName = reader.readElementText().trimmed();
        } else if ( element == RECEIVERAMAIL ) {
          receiveremail = reader.readElementText().trimmed();
        } else if ( element == ID ) {
          id = reader.readElementText().trimmed();
        } else if ( element == ERROR ) {
          error.key = reader.attributes().value(KEY).toString();
          error.desc = reader.readElementText().trimmed();
          error.hasError = true;
        }  else {
          reader.raiseError(QString("Invalid element: %1").arg(element));
        }
        break;
      }
      case QXmlStreamReader::EndElement: {
        element = reader.name().toString();
        if ( element == PACK ) {
          return;
        }
        break;
      }
      case QXmlStreamReader::EndDocument:
      case QXmlStreamReader::Comment:
      case QXmlStreamReader::Characters:
        break;
      default:
        reader.raiseError("Unexpected token");
        break;
    }
  }
}

const PackageCollection
Package::parseList(const QByteArray &data, Error &error) {
  PackageList list;
  QString startDate;
  QString endDate;
  QXmlStreamReader reader(data);
  while (!reader.atEnd()) {
    reader.readNext();
    switch (reader.tokenType()) {
    case QXmlStreamReader::StartElement: {
      QString element = reader.name().toString();
      if ( element == START ) {
        break;
      } else if ( element == PACK ) {
        Package pack;
        pack.load(reader);
        list.append(pack);
      } else if ( element == STARTDATE ) {
        startDate = reader.readElementText().trimmed();
      } else if ( element == ENDDATE ) {
        endDate = reader.readElementText().trimmed();
      } else if ( element == ERROR ) {
        error.key = reader.attributes().value(KEY).toString();
        error.desc = reader.readElementText().trimmed();
        error.hasError = true;
      } else if ( element == RESULTS ) {
        int results = reader.readElementText().trimmed().toInt();
        if ( list.size() != results )
          qDebug() << "Why?";
      } else if ( element == CUSTOMER ) {
          //ignore
      } else {
        reader.raiseError(QString("Invalid element: %1").arg(element));
      }
      break;
    }
    case QXmlStreamReader::EndElement:
    case QXmlStreamReader::EndDocument:
    case QXmlStreamReader::Comment:
    case QXmlStreamReader::Characters:
      break;
    default:
      break;
    }
  }
  if (reader.hasError()) {
      error.internalError = QObject::tr("Error parse data: %2, at line %3, column %4")
                  .arg(reader.errorString())
                  .arg(reader.lineNumber())
                  .arg(reader.columnNumber());
      error.hasError = true;
      error.data = data;
  }
  PackageCollection collection;
  collection.startDate = startDate;
  collection.endDate = endDate;
  collection.packages = list;
  return collection;
}

const QString
Package::packageDesc(const Package &package) {
  if ( "Created" == package.status ) {
    return QObject::trUtf8("Created");
  } else if ( "Prepared" == package.status ) {
    return QObject::trUtf8("Prepared");
  } else if ( "Sent" == package.status ) {
    return QObject::trUtf8("Sent");
  } else if ( "InTransit" == package.status ) {
    return QObject::trUtf8("InTransit");
  } else if ( "Stored" == package.status ) {
    return QObject::trUtf8("Stored");
  } else if ( "Delivered" == package.status ) {
    return QObject::trUtf8("Delivered");
  } else if ( "Avizo" == package.status ) {
    return QObject::trUtf8("Avizo");
  } else if ( "Expired" == package.status ) {
    return QObject::trUtf8("Expired");
  } else if ( "ReturnedToAgency" == package.status ) {
    return QObject::trUtf8("ReturnedToAgency");
  } else if ( "DeliveredToAgency" == package.status ) {
    return QObject::trUtf8("DeliveredToAgency");
  } else if ( "ReturnedToSortingCenter" == package.status ) {
    return QObject::trUtf8("ReturnedToSortingCenter");
  } else if ( "DeliveredToSortingCenter" == package.status ) {
    return QObject::trUtf8("DeliveredToSortingCenter");
  } else if ( "ReturnedTosender" == package.status ) {
    return QObject::trUtf8("ReturnedTosender");
  } else if ( "Cancelled" == package.status ) {
    return QObject::trUtf8("Cancelled");
  }
  return QObject::trUtf8("Unknown");
}

const QString
Package::packageStatus(const Package &package) {
  if ( "Created" == package.status ) {
    return QObject::trUtf8("Created");
  } else if ( "Prepared" == package.status ) {
    return QObject::trUtf8("Prepared");
  } else if ( "Sent" == package.status ) {
    return QObject::trUtf8("Sent");
  } else if ( "InTransit" == package.status ) {
    return QObject::trUtf8("InTransit");
  } else if ( "Stored" == package.status ) {
    return QObject::trUtf8("Stored");
  } else if ( "Delivered" == package.status ) {
    return QObject::trUtf8("Delivered");
  } else if ( "Avizo" == package.status ) {
    return QObject::trUtf8("Avizo");
  } else if ( "Expired" == package.status ) {
    return QObject::trUtf8("Expired");
  } else if ( "ReturnedToAgency" == package.status ) {
    return QObject::trUtf8("ReturnedToAgency");
  } else if ( "DeliveredToAgency" == package.status ) {
    return QObject::trUtf8("DeliveredToAgency");
  } else if ( "ReturnedToSortingCenter" == package.status ) {
    return QObject::trUtf8("ReturnedToSortingCenter");
  } else if ( "DeliveredToSortingCenter" == package.status ) {
    return QObject::trUtf8("DeliveredToSortingCenter");
  } else if ( "ReturnedTosender" == package.status ) {
    return QObject::trUtf8("ReturnedTosender");
  } else if ( "Cancelled" == package.status ) {
    return QObject::trUtf8("Cancelled");
  }
  return QObject::trUtf8("Unknown");
}

/** struct Payment */
void
Payment::load(QXmlStreamReader &reader) {
  QString element = reader.name().toString();
  if ( element != PAYMENT ) {
    reader.raiseError("Illegal tag name");
    return;
  }
  while ( !reader.atEnd() ) {
    reader.readNext();
    switch ( reader.tokenType() ) {
      case QXmlStreamReader::StartElement: {
        element = reader.name().toString();
        if ( element == PACKCODE ) {
          packcode = reader.readElementText().trimmed();
        } else if ( element == AMOUNT ) {
          amount = reader.readElementText().trimmed();
        } else if ( element == POSDESC ) {
          posdesc = reader.readElementText().trimmed();
        } else if ( element == TRANSACTIONDATE ) {
          transactionDate = reader.readElementText().trimmed();
        } else if ( element == BOXMACHINENAME ) {
          boxMachineName = reader.readElementText().trimmed();
        } else if ( element == COMISSIONFORCOD ) {
          comissionForCod = reader.readElementText().trimmed();
        } else if ( element == DATEOFPARCELDELIVERED ) {
          dateOfParceDelivered = reader.readElementText().trimmed();
        } else if ( element == ID ) {
          id = reader.readElementText().trimmed();
        } else if ( element == PARCELBARCODE ) {
          parcelBarcode = reader.readElementText().trimmed();
        } else if ( element == PRICEFORDELIVERY ) {
          priceForDelivery = reader.readElementText().trimmed();
        } else if ( element == RECEIVEDCOD ) {
          receivedCod = reader.readElementText().trimmed();
        } else {
          reader.raiseError(QString("Invalid element: %1").arg(element));
        }
        break;
      }
      case QXmlStreamReader::EndElement: {
        element = reader.name().toString();
        if ( element == PAYMENT ) {
          return;
        }
        break;
      }
      case QXmlStreamReader::EndDocument:
      case QXmlStreamReader::Comment:
      case QXmlStreamReader::Characters:
        break;
      default:
        reader.raiseError("Unexpected token");
        break;
    }
  }
}

const PaymentCollection
Payment::parseList(const QByteArray &data, Error &error) {
  PaymentList list;
  QString startDate;
  QString endDate;
  QXmlStreamReader reader(data);
  while (!reader.atEnd()) {
    reader.readNext();
    switch (reader.tokenType()) {
    case QXmlStreamReader::StartElement: {
      QString element = reader.name().toString();
      if ( element == START ) {
        break;
      } else if ( element == PAYMENT ) {
        Payment payment;
        payment.load(reader);
        list.append(payment);
      } else if ( element == STARTDATE ) {
        startDate = reader.readElementText().trimmed();
      } else if ( element == ENDDATE ) {
        endDate = reader.readElementText().trimmed();
      } else if ( element == ERROR ) {
        error.key = reader.attributes().value(KEY).toString();
        error.desc = reader.readElementText().trimmed();
        error.hasError = true;
      } else if ( element == RESULTS ) {
        int results = reader.readElementText().trimmed().toInt();
        if ( list.size() != results )
          qDebug() << "Why?";
      } else if ( element == CUSTOMER ) {
          //ignore
      } else {
        reader.raiseError(QString("Invalid element: %1").arg(element));
      }
      break;
    }
    case QXmlStreamReader::EndElement:
    case QXmlStreamReader::EndDocument:
    case QXmlStreamReader::Comment:
    case QXmlStreamReader::Characters:
      break;
    default:
      break;
    }
  }
  if (reader.hasError()) {
      error.internalError = QObject::tr("Error parse data: %2, at line %3, column %4")
                  .arg(reader.errorString())
                  .arg(reader.lineNumber())
                  .arg(reader.columnNumber());
      error.hasError = true;
      error.data = data;
  }
  PaymentCollection collection;
  collection.startDate = startDate;
  collection.endDate = endDate;
  collection.payments = list;
  return collection;
}

/** struct Station */
void
Station::load(QXmlStreamReader &reader) {
  QString element = reader.name().toString();
  if ( element != STATION ) {
    reader.raiseError("Illegal tag name");
    return;
  }
  while ( !reader.atEnd() ) {
    reader.readNext();
    switch ( reader.tokenType() ) {
      case QXmlStreamReader::StartElement: {
        element = reader.name().toString();
        if ( element == METROSTATIONSNAME ) {
          metroStationName = reader.readElementText().trimmed();
        } else if ( element == TOWN ) {
          town = reader.readElementText().trimmed();
        } else if ( element == LATITUDE ) {
          latitude = reader.readElementText().trimmed();
        } else if ( element == LONGITUDE ) {
          longitude = reader.readElementText().trimmed();
        } else {
          reader.raiseError(QString("Invalid element: %1").arg(element));
        }
        break;
      }
      case QXmlStreamReader::EndElement: {
        element = reader.name().toString();
        if ( element == STATION ) {
          return;
        }
        break;
      }
      case QXmlStreamReader::EndDocument:
      case QXmlStreamReader::Comment:
      case QXmlStreamReader::Characters:
        break;
      default:
        reader.raiseError("Unexpected token");
        break;
    }
  }
}

const StationList
Station::parseList(const QByteArray &data, Error &error) {
  StationList list;
  QXmlStreamReader reader(data);
  while (!reader.atEnd()) {
    reader.readNext();
    switch (reader.tokenType()) {
    case QXmlStreamReader::StartElement: {
      QString element = reader.name().toString();
      if ( element == START ) {
        break;
      } else if ( element == STATION ) {
        Station station;
        station.load(reader);
        list.append(station);
      } else if ( element == ERROR ) {
        error.key = reader.attributes().value(KEY).toString();
        error.desc = reader.readElementText().trimmed();
        error.hasError = true;
      } else if ( element == CUSTOMER ) {
          //ignore
      } else {
        reader.raiseError(QString("Invalid element: %1").arg(element));
      }
      break;
    }
    case QXmlStreamReader::EndElement:
    case QXmlStreamReader::EndDocument:
    case QXmlStreamReader::Comment:
    case QXmlStreamReader::Characters:
      break;
    default:
      break;
    }
  }
  if (reader.hasError()) {
      error.internalError = QObject::tr("Error parse data: %2, at line %3, column %4")
                  .arg(reader.errorString())
                  .arg(reader.lineNumber())
                  .arg(reader.columnNumber());
      error.hasError = true;
      error.data = data;
  }
  return list;
}

/** struct PackageReg */
const QString
PackageReg::toXml(int tab) const {
  QString result;
  QXmlStreamWriter writer(&result);
  writer.setAutoFormattingIndent(tab);
  writer.writeStartElement("pack");
  private_writeElement(writer, "id", id);
  private_writeElement(writer, "addressPhoneNumber", addressPhoneNumber);
  private_writeElement(writer, "senderPhoneNumber", senderPhoneNumber);
  private_writeElement(writer, "boxMachineName", boxMachineName);
  private_writeElement(writer, "packType", packType);
  private_writeElement(writer, "onDeliveryAmount", onDeliveryAmount);
  private_writeElement(writer, "customerRef", customerRef);
  writer.writeEndElement();
  return result;
}

const QString
PackageReg::toXml(const PackageRegList &list, bool autoLabel, int tab) {
  QString result;
  QTextStream stream(&result);


  stream << "<paczkomaty>";
  stream << "<autoLabels>" << (autoLabel ? "1" : "0") << "<autoLabels>";
  PackageRegListIterator it(list);
  while ( it.hasNext() ) {
    const PackageReg reg = it.next();
    stream << reg.toXml(tab);
  }
  stream << "</paczkomaty>";
  return result;
}

const QString
PackageReg::toXml(const QStringList packcodes, bool testPrintOut) {
  QString result;
  QTextStream stream(&result);

  stream << "<paczkomaty>";
  stream << "<testprintout>" << (testPrintOut ? "1" : "0") << "<testprintout>";
  QStringListIterator it(packcodes);
  while ( it.hasNext() ) {
    stream << "<pack>" << "<packcode>" << it.next() << "</packcode>" << "</pack>";
  }
  stream << "</paczkomaty>";
  return result;
}



