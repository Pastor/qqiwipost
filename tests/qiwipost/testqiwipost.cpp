/**************************************************************************
**
** This file is part of Gateway
**
** Copyright (c) 2012 NII Voskhod and/or its subsidiary(-ies).
**
** Contact: NII Voskhod (info@nii.voskhod.ru)
**
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** Other Usage
**
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
** If you have questions regarding the use of this file, please contact
** NII Voskhod at info@nii.voskhod.ru.
**
**************************************************************************/

#include <QTest>
#include <QDebug>
#include <qiwipost/dao.h>
#include <qiwipost/qiwipost.h>

static const uchar test_data [] = {
  0xc3, 0x02, 0x00, 0x38, 0x4b, 0xe8
  /**
   * 11000011, 00000010, 00000000, 00111000, 01001011, 11101000
   * 110000110000001000000000001110000100101111101000
   *
   *
   *
   */
};

using namespace Qiwi;

class TestQiwiPost: public QObject {
    Q_OBJECT
  private slots:
    void testGet_data();
    void testGet();
};


void
TestQiwiPost::testGet_data() {
  PackageReg reg;
  reg.id = "1";
  reg.addressPhoneNumber = "2";
  reg.boxMachineName = "3";
  reg.customerRef = "4";
  reg.onDeliveryAmount = "5";
  reg.packType = "6";
  reg.senderPhoneNumber = "7";
  qDebug() << PackageReg::toXml(PackageRegList() << reg);

//  gBitArray data;

//  data.setRawData( (char *)test_data, sizeof(test_data) );
//  QTest::addColumn<qlonglong>("origbyte");
//  QTest::addColumn<qlonglong>("getbyte");

//  QTest::newRow("1 byte") <<
//    (qlonglong)0xc3 << (qlonglong)data.get(0,  8);
//  QTest::newRow("2 byte") <<
//    (qlonglong)0x02 << (qlonglong)data.get(8,  8);
//  QTest::newRow("3 byte") <<
//    (qlonglong)0x00 << (qlonglong)data.get(16, 8);
//  QTest::newRow("4 byte") <<
//    (qlonglong)0x38 << (qlonglong)data.get(24, 8);
//  QTest::newRow("5 byte") <<
//    (qlonglong)0x4b << (qlonglong)data.get(32, 8);
//  QTest::newRow("6 byte") <<
//    (qlonglong)0xe8 << (qlonglong)data.get(40, 8);
//  //C30200384BE8
//  QTest::newRow("0-2 bytes") <<
//    (qlonglong)0xc30200 << (qlonglong)data.get(0, 24);
//  QTest::newRow("1-3 bytes") <<
//    (qlonglong)0x020038 << (qlonglong)data.get(8, 24);
//  QTest::newRow("2-4 bytes") <<
//    (qlonglong)0x00384b << (qlonglong)data.get(16, 24);
//  QTest::newRow("1-4 bytes") <<
//    (qlonglong)0x0200384b << (qlonglong)data.get(8, 32);
//  QTest::newRow("0-5 bytes") <<
//    (qlonglong)0xc30200384be8 << (qlonglong)data.get(0, 48);
}

void
TestQiwiPost::testGet() {
//  QFETCH(qlonglong, origbyte);
//  QFETCH(qlonglong, getbyte);

//  QCOMPARE(origbyte, getbyte);
}


QTEST_MAIN(TestQiwiPost)
#include "testqiwipost.moc"
