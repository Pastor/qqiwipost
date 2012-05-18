#ifndef QIWIERRORVIEW_H
#define QIWIERRORVIEW_H

#include <QDialog>
#include <qiwipost/dao.h>
#include "qiwigui_global.h"

namespace Ui {
  class QiwiErrorView;
}

namespace Qiwi {

class QIWIGUISHARED_EXPORT QiwiErrorView : public QDialog {
  Q_OBJECT

public:
  QiwiErrorView(QWidget *parent = 0);
  ~QiwiErrorView();

  int showError(const Error &error);
private:
  Ui::QiwiErrorView *ui;
};

}

#endif // QIWIERRORVIEW_H
