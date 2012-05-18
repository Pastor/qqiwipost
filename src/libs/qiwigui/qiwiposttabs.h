#ifndef QIWIPOSTTABS_H
#define QIWIPOSTTABS_H

#include <QWidget>
#include "qiwigui_global.h"

namespace Ui {
class QiwiPostTabs;
}

namespace Qiwi {

class QIWIGUISHARED_EXPORT QiwiPostTabs : public QWidget {
    Q_OBJECT
  public:
    QiwiPostTabs(QWidget *parent = 0);
    ~QiwiPostTabs();

    void setInfo(QWidget *w);

    void setEnabledUpdatePackage(bool value);
  protected slots:
    void proxy_updatePackages();
  signals:
    void updatePackages();
  private:
    Ui::QiwiPostTabs *ui;
};

}

#endif // QIWIPOSTTABS_H
