/********************************************************************************
** Form generated from reading UI file 'qiwiguimachineview.ui'
**
** Created: Fri 18. May 15:52:49 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QIWIGUIMACHINEVIEW_H
#define UI_QIWIGUIMACHINEVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableView>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QiwiGuiMachineView
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *tvMachines;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget;
    QFormLayout *formLayout;
    QLabel *lblName;
    QLineEdit *leName;
    QLabel *lblPostCode;
    QLineEdit *lePostCode;
    QLabel *lblStreet;
    QLineEdit *leStreet;
    QLabel *lblBuilding;
    QLineEdit *leBuilding;
    QLabel *lblTown;
    QLineEdit *leTown;
    QWidget *widget_2;
    QFormLayout *formLayout_2;
    QLabel *lblProvince;
    QLineEdit *leProvince;
    QLabel *lblStatus;
    QLineEdit *leStatus;
    QLabel *lblWork;
    QLineEdit *leWork;
    QTextEdit *teLocationDesc;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbSelect;

    void setupUi(QDialog *QiwiGuiMachineView)
    {
        if (QiwiGuiMachineView->objectName().isEmpty())
            QiwiGuiMachineView->setObjectName(QString::fromUtf8("QiwiGuiMachineView"));
        QiwiGuiMachineView->setWindowModality(Qt::WindowModal);
        QiwiGuiMachineView->resize(630, 601);
        QFont font;
        font.setFamily(QString::fromUtf8("DejaVu Sans Mono"));
        QiwiGuiMachineView->setFont(font);
        QiwiGuiMachineView->setModal(true);
        verticalLayout = new QVBoxLayout(QiwiGuiMachineView);
        verticalLayout->setSpacing(2);
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tvMachines = new QTableView(QiwiGuiMachineView);
        tvMachines->setObjectName(QString::fromUtf8("tvMachines"));
        tvMachines->setSelectionMode(QAbstractItemView::SingleSelection);
        tvMachines->setSelectionBehavior(QAbstractItemView::SelectRows);
        tvMachines->setGridStyle(Qt::DashLine);

        verticalLayout->addWidget(tvMachines);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        widget = new QWidget(QiwiGuiMachineView);
        widget->setObjectName(QString::fromUtf8("widget"));
        formLayout = new QFormLayout(widget);
        formLayout->setContentsMargins(2, 2, 2, 2);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setHorizontalSpacing(2);
        formLayout->setVerticalSpacing(2);
        lblName = new QLabel(widget);
        lblName->setObjectName(QString::fromUtf8("lblName"));

        formLayout->setWidget(0, QFormLayout::LabelRole, lblName);

        leName = new QLineEdit(widget);
        leName->setObjectName(QString::fromUtf8("leName"));

        formLayout->setWidget(0, QFormLayout::FieldRole, leName);

        lblPostCode = new QLabel(widget);
        lblPostCode->setObjectName(QString::fromUtf8("lblPostCode"));

        formLayout->setWidget(1, QFormLayout::LabelRole, lblPostCode);

        lePostCode = new QLineEdit(widget);
        lePostCode->setObjectName(QString::fromUtf8("lePostCode"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lePostCode);

        lblStreet = new QLabel(widget);
        lblStreet->setObjectName(QString::fromUtf8("lblStreet"));

        formLayout->setWidget(2, QFormLayout::LabelRole, lblStreet);

        leStreet = new QLineEdit(widget);
        leStreet->setObjectName(QString::fromUtf8("leStreet"));

        formLayout->setWidget(2, QFormLayout::FieldRole, leStreet);

        lblBuilding = new QLabel(widget);
        lblBuilding->setObjectName(QString::fromUtf8("lblBuilding"));

        formLayout->setWidget(3, QFormLayout::LabelRole, lblBuilding);

        leBuilding = new QLineEdit(widget);
        leBuilding->setObjectName(QString::fromUtf8("leBuilding"));

        formLayout->setWidget(3, QFormLayout::FieldRole, leBuilding);

        lblTown = new QLabel(widget);
        lblTown->setObjectName(QString::fromUtf8("lblTown"));

        formLayout->setWidget(4, QFormLayout::LabelRole, lblTown);

        leTown = new QLineEdit(widget);
        leTown->setObjectName(QString::fromUtf8("leTown"));

        formLayout->setWidget(4, QFormLayout::FieldRole, leTown);


        horizontalLayout_2->addWidget(widget);

        widget_2 = new QWidget(QiwiGuiMachineView);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        formLayout_2 = new QFormLayout(widget_2);
        formLayout_2->setContentsMargins(2, 2, 2, 2);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setHorizontalSpacing(2);
        formLayout_2->setVerticalSpacing(2);
        lblProvince = new QLabel(widget_2);
        lblProvince->setObjectName(QString::fromUtf8("lblProvince"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, lblProvince);

        leProvince = new QLineEdit(widget_2);
        leProvince->setObjectName(QString::fromUtf8("leProvince"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, leProvince);

        lblStatus = new QLabel(widget_2);
        lblStatus->setObjectName(QString::fromUtf8("lblStatus"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, lblStatus);

        leStatus = new QLineEdit(widget_2);
        leStatus->setObjectName(QString::fromUtf8("leStatus"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, leStatus);

        lblWork = new QLabel(widget_2);
        lblWork->setObjectName(QString::fromUtf8("lblWork"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, lblWork);

        leWork = new QLineEdit(widget_2);
        leWork->setObjectName(QString::fromUtf8("leWork"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, leWork);

        teLocationDesc = new QTextEdit(widget_2);
        teLocationDesc->setObjectName(QString::fromUtf8("teLocationDesc"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, teLocationDesc);


        horizontalLayout_2->addWidget(widget_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pbSelect = new QPushButton(QiwiGuiMachineView);
        pbSelect->setObjectName(QString::fromUtf8("pbSelect"));
        pbSelect->setMinimumSize(QSize(0, 32));
        pbSelect->setMaximumSize(QSize(16777215, 32));

        horizontalLayout->addWidget(pbSelect);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(QiwiGuiMachineView);

        QMetaObject::connectSlotsByName(QiwiGuiMachineView);
    } // setupUi

    void retranslateUi(QDialog *QiwiGuiMachineView)
    {
        QiwiGuiMachineView->setWindowTitle(QApplication::translate("QiwiGuiMachineView", "Dialog", 0, QApplication::UnicodeUTF8));
        lblName->setText(QApplication::translate("QiwiGuiMachineView", "Name", 0, QApplication::UnicodeUTF8));
        lblPostCode->setText(QApplication::translate("QiwiGuiMachineView", "PostCode", 0, QApplication::UnicodeUTF8));
        lblStreet->setText(QApplication::translate("QiwiGuiMachineView", "Street", 0, QApplication::UnicodeUTF8));
        lblBuilding->setText(QApplication::translate("QiwiGuiMachineView", "Building", 0, QApplication::UnicodeUTF8));
        lblTown->setText(QApplication::translate("QiwiGuiMachineView", "Town", 0, QApplication::UnicodeUTF8));
        lblProvince->setText(QApplication::translate("QiwiGuiMachineView", "Province", 0, QApplication::UnicodeUTF8));
        lblStatus->setText(QApplication::translate("QiwiGuiMachineView", "Status", 0, QApplication::UnicodeUTF8));
        lblWork->setText(QApplication::translate("QiwiGuiMachineView", "Work", 0, QApplication::UnicodeUTF8));
        pbSelect->setText(QApplication::translate("QiwiGuiMachineView", "Select", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QiwiGuiMachineView: public Ui_QiwiGuiMachineView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QIWIGUIMACHINEVIEW_H
