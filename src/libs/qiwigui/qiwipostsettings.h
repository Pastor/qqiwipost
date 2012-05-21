#ifndef QIWIPOSTSETTINGS_H
#define QIWIPOSTSETTINGS_H

#include <QDialog>
#include <qiwipost/qiwipost.h>
#include "qiwigui_global.h"

namespace Ui {
class QiwiPostSettings;
}

namespace Qiwi {

class QIWIGUISHARED_EXPORT QiwiPostSettings : public QDialog {
    Q_OBJECT
  public:
    QiwiPostSettings(QWidget *parent = 0);
    ~QiwiPostSettings();
    
    int show(QiwiPost *post);
  protected slots:
    void save();
  private:
    Ui::QiwiPostSettings *ui;
    QiwiPost *tmpPost;
};

}

#endif // QIWIPOSTSETTINGS_H
