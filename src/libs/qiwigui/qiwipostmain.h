#ifndef QIWIPOSTMAIN_H
#define QIWIPOSTMAIN_H

#include <QMainWindow>
#include <QTableView>
#include <qiwipost/qiwipost.h>
#include "qiwiguimodel.h"
#include "qiwiguimachineview.h"
#include "qiwipostpackageview.h"
#include "qiwiposttabs.h"
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
  private:
    Ui::QiwiPostMain *ui;
    QiwiGuiMachineView *mw;
    QiwiPostPackageTableModel *pm;
    QTableView       *tvPackages;
    QiwiPost         *post;
    QiwiPostTabs     *tabs;
    QiwiPostPackageView *packView;
};

}

#endif // QIWIPOSTMAIN_H
