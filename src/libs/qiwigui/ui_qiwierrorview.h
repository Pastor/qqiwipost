/********************************************************************************
** Form generated from reading UI file 'qiwierrorview.ui'
**
** Created: Fri 18. May 14:39:24 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QIWIERRORVIEW_H
#define UI_QIWIERRORVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QiwiErrorView
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *teError;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pbOk;
    QPushButton *pbSend;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *QiwiErrorView)
    {
        if (QiwiErrorView->objectName().isEmpty())
            QiwiErrorView->setObjectName(QString::fromUtf8("QiwiErrorView"));
        QiwiErrorView->setWindowModality(Qt::WindowModal);
        QiwiErrorView->resize(419, 244);
        QFont font;
        font.setFamily(QString::fromUtf8("DejaVu Sans Mono"));
        QiwiErrorView->setFont(font);
        QiwiErrorView->setModal(true);
        verticalLayout = new QVBoxLayout(QiwiErrorView);
        verticalLayout->setSpacing(2);
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        teError = new QTextEdit(QiwiErrorView);
        teError->setObjectName(QString::fromUtf8("teError"));
        teError->setReadOnly(true);

        verticalLayout->addWidget(teError);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pbOk = new QPushButton(QiwiErrorView);
        pbOk->setObjectName(QString::fromUtf8("pbOk"));
        pbOk->setMinimumSize(QSize(0, 32));
        pbOk->setMaximumSize(QSize(16777215, 32));

        horizontalLayout->addWidget(pbOk);

        pbSend = new QPushButton(QiwiErrorView);
        pbSend->setObjectName(QString::fromUtf8("pbSend"));
        pbSend->setMinimumSize(QSize(0, 32));
        pbSend->setMaximumSize(QSize(16777215, 32));

        horizontalLayout->addWidget(pbSend);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(QiwiErrorView);

        QMetaObject::connectSlotsByName(QiwiErrorView);
    } // setupUi

    void retranslateUi(QDialog *QiwiErrorView)
    {
        QiwiErrorView->setWindowTitle(QApplication::translate("QiwiErrorView", "Dialog", 0, QApplication::UnicodeUTF8));
        pbOk->setText(QApplication::translate("QiwiErrorView", "ok", 0, QApplication::UnicodeUTF8));
        pbSend->setText(QApplication::translate("QiwiErrorView", "Send", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QiwiErrorView: public Ui_QiwiErrorView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QIWIERRORVIEW_H
