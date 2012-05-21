#ifndef QIWIPOSTTABS_H
#define QIWIPOSTTABS_H

#include <QWidget>
#include <qiwipost/qiwipost.h>
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
    void setData(QiwiPost *post, const Package &package);

    void setEnabledUpdatePackage(bool value);
    void setEnabledAppendPackage(bool value);
    void setEnabledRemovePackage(bool value);
    void setEnabledSendPackage(bool value);
    void setEnabledEditPackage(bool value);
  protected slots:
    void proxy_updatePackages();
    void proxy_appendPackage();
    void proxy_removePackage();
    void proxy_sendPackage();
    void proxy_editPackage();

    void labelOpen();
  signals:
    void updatePackages();
    void appendPackage();
    void removePackage();
    void sendPackage();
    void editPackage();
  private:
    Ui::QiwiPostTabs *ui;
    QiwiPost         *post;
    Package          package;
};

}

#endif // QIWIPOSTTABS_H
