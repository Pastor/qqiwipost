#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QTextStream>
#include "dao.h"

namespace Qiwi {
namespace Internal {
  static inline void
  private_writeElement(QXmlStreamWriter &writer, QString elementName, QString elementValue) {
    writer.writeTextElement(elementName, elementValue);
  }



  static const char * const START = "paczkomaty";
  static const char * const ERROR = "error";
  static const char * const STATUS = "status";
  static const char * const KEY = "key";
  static const char * const MACHINE = "machine";
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
      return false;
      break;
    }
  }
  return false;
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
    qDebug() << QObject::tr("Error parse data: %2, at line %3, column %4")
                .arg(reader.errorString())
                .arg(reader.lineNumber())
                .arg(reader.columnNumber());
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
        } else {
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
      } else if ( element == RESULTS ) {
        int results = reader.readElementText().trimmed().toInt();
        if ( list.size() != results )
          qDebug() << "Why?";
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
    qDebug() << QObject::tr("Error parse data: %2, at line %3, column %4")
                .arg(reader.errorString())
                .arg(reader.lineNumber())
                .arg(reader.columnNumber());
  }
  PackageCollection collection;
  collection.startDate = startDate;
  collection.endDate = endDate;
  collection.packages = list;
  return collection;
}

/** struct PackageReg */
const QString
PackageReg::toXml(int tab) const {
  QString result;
  QXmlStreamWriter writer(&result);
  writer.setAutoFormattingIndent(tab);
  writer.writeStartElement("pack");
  private_writeElement(writer, "id", id);
  private_writeElement(writer, "adreseePhoneNumber", addressPhoneNumber);
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



