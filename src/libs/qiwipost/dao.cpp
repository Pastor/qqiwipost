#include <QDebug>
#include <QXmlStreamWriter>
#include <QTextStream>
#include "dao.h"

namespace Qiwi {
  static inline void
  private_writeElement(QXmlStreamWriter &writer, QString elementName, QString elementValue) {
    writer.writeTextElement(elementName, elementValue);
  }

}

using namespace Qiwi;

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


