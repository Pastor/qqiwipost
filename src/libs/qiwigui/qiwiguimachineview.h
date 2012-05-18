#ifndef QIWIGUIMACHINEVIEW_H
#define QIWIGUIMACHINEVIEW_H

#include <QDialog>
#include <qiwipost/qiwipost.h>
#include "qiwiguimodel.h"
#include "qiwigui_global.h"

namespace Ui {
  class QiwiGuiMachineView;
}

namespace Qiwi {

class QIWIGUISHARED_EXPORT QiwiGuiMachineView : public QDialog {
  Q_OBJECT
public:
  QiwiGuiMachineView(QWidget *parent = 0);
  ~QiwiGuiMachineView();

  void listUpdate(QiwiPost *post);
  const Machine selectedMachine() const;
signals:
  void selectedMachine(const Machine &machine);
protected slots:
  void select();
  void currentRowChanged(const QModelIndex &current, const QModelIndex &previous);
  void triggeredMachine(const Machine &machine);
private:
  Ui::QiwiGuiMachineView *ui;
  QiwiPostMachineTableModel *mm;
};

}

#endif // QIWIGUIMACHINEVIEW_H
