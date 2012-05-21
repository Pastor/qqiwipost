#ifndef QIWIPOSTSENDPACKAGES_H
#define QIWIPOSTSENDPACKAGES_H

#include <QDialog>
#include <qiwipost/qiwipost.h>
#include "qiwigui_global.h"

namespace Ui {
class QiwiPostSendPackages;
}

namespace Qiwi {

class QIWIGUISHARED_EXPORT  QiwiPostSendPackages : public QDialog {
    Q_OBJECT
  public:
    QiwiPostSendPackages(QWidget *parent = 0);
    ~QiwiPostSendPackages();
    
    void  show(QiwiPost *post);
  protected slots:
    void  sendPackages();
    void  reload();
  private:
    Ui::QiwiPostSendPackages *ui;
    QiwiPost *post;

};

}

#endif // QIWIPOSTSENDPACKAGES_H
