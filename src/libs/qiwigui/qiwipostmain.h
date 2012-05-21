#ifndef QIWIPOSTMAIN_H
#define QIWIPOSTMAIN_H

#include <QMainWindow>
#include <QTableView>
#include <qiwipost/qiwipost.h>
#include "qiwiguimodel.h"
#include "qiwipostpackageview.h"
#include "qiwiposttabs.h"
#include "qiwipostsettings.h"
#include "qiwipostsendpackages.h"
#include "qiwipostregisterpackage.h"
#include "qiwigui_global.h"

namespace Ui {
class QiwiPostMain;
}

namespace Qiwi {

class QIWIGUISHARED_EXPORT QiwiPostMain : public QMainWindow {
    Q_OBJECT
  public:
    QiwiPostMain(QWidget *parent = 0);
    ~QiwiPostMain();

    void loadSettings(const QString &filename);

  public slots:
    void applaySettings();
    void saveSettings();
    void reload();
    void selectMachines();
  protected slots:
    void currentRowChanged(const QModelIndex &current, const QModelIndex &previous);
    void showSettings();
    void showSendPackages();
    void showRegisterPackage();
    void showEditPackage();
    void showUnregisterPackage();
  private:
    Ui::QiwiPostMain *ui;
    QiwiPostPackageTableModel *pm;
    QTableView       *tvPackages;
    QiwiPost         *post;
    QiwiPostTabs     *tabs;
    QiwiPostPackageView *packView;
    QiwiPostSettings *qps;
    QiwiPostSendPackages *qsp;
    QiwiPostRegisterPackage *qrp;
    Package           currentPackage;
};

}

#endif // QIWIPOSTMAIN_H
