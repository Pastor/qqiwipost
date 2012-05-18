#ifndef QIWIPOSTPACKAGEVIEW_H
#define QIWIPOSTPACKAGEVIEW_H

#include <QWidget>
#include <qiwipost/dao.h>
#include <qiwipost/qiwipost.h>
#include "qiwigui_global.h"


namespace Ui {
class QiwiPostPackageView;
}

namespace Qiwi {

class QIWIGUISHARED_EXPORT QiwiPostPackageView : public QWidget {
    Q_OBJECT
    
  public:

    enum Mode {
      New,
      Info,
      Edit
    };

    QiwiPostPackageView(QWidget *parent = 0);
    ~QiwiPostPackageView();

    void load(QiwiPost *post, const Package &package);

    const Package    package(QiwiPost *post) const;
    const PackageReg packageReg(QiwiPost *post) const;

    void setMode(Mode mode);

  public slots:
    void reset();
    void preinit(QiwiPost *post);
    void setEnabledElements(bool value);
  private:
    Ui::QiwiPostPackageView *ui;
};

}

#endif // QIWIPOSTPACKAGEVIEW_H
