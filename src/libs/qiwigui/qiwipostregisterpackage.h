#ifndef QIWIPOSTREGISTERPACKAGE_H
#define QIWIPOSTREGISTERPACKAGE_H

#include <QDialog>
#include <QRegExpValidator>
#include <qiwipost/qiwipost.h>
#include <qiwigui/qiwiguimachineview.h>
#include "qiwigui_global.h"

namespace Ui {
class QiwiPostRegisterPackage;
}

namespace Qiwi {

class QIWIGUISHARED_EXPORT QiwiPostRegisterPackage : public QDialog {
    Q_OBJECT
  public:
    QiwiPostRegisterPackage(QWidget *parent = 0);
    ~QiwiPostRegisterPackage();

    int  show(QiwiPost *post, const Package &package);
    void setEditMode(bool value);    
    bool isValid() const;
  protected slots:
    void  registerPackage();
    void  selectMachine();
    void  cancle();
  private:
    Ui::QiwiPostRegisterPackage *ui;
    QiwiGuiMachineView          *mw;
    QiwiPost                    *post;
    QRegExpValidator            *rexv;
    Package                     editPackage;
    bool                        editMode;
};

}

#endif // QIWIPOSTREGISTERPACKAGE_H
