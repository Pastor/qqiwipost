#include <qiwipost/dao.h>
#include <qiwigui/qiwigui.h>
#include "qiwipostsettings.h"
#include "ui_qiwipostsettings.h"

using namespace Qiwi;

QiwiPostSettings::QiwiPostSettings(QWidget *parent) :
  QDialog(parent), ui(new Ui::QiwiPostSettings), tmpPost(0) {
  ui->setupUi(this);
  QiwiGuiUtils::setToolStyle(this);
  connect(ui->pbSave, SIGNAL(clicked()), this, SLOT(save()));
}

QiwiPostSettings::~QiwiPostSettings() {
  delete ui;
}

int
QiwiPostSettings::show(QiwiPost *post) {
  tmpPost = post;

  ui->lePassword->setText(post->getProperty(QiwiPost::QIWIPOST_PASSWORD));
  ui->leUsername->setText(post->getProperty(QiwiPost::QIWIPOST_USERNAME));
  ui->leUrl->setText(post->getProperty(QiwiPost::QIWIPOST_URL));
  QString timeout = post->getProperty(QiwiPost::QIWIPOST_TIMEOUT);
  if ( timeout == 0 || timeout.isEmpty() ) {
    timeout = "20000";
  }
  ui->sbTimeout->setValue(timeout.toInt() / 1000);
  setModal(true);
  setVisible(true);
  return exec();
}

void
QiwiPostSettings::save() {
  if ( tmpPost == 0 )
    return;
  tmpPost->putProperty(QiwiPost::QIWIPOST_PASSWORD, ui->lePassword->text());
  tmpPost->putProperty(QiwiPost::QIWIPOST_USERNAME, ui->leUsername->text());
  tmpPost->putProperty(QiwiPost::QIWIPOST_URL, ui->leUrl->text());
  tmpPost->putProperty(QiwiPost::QIWIPOST_TIMEOUT,
                       QString::number(ui->sbTimeout->value() * 1000));
  tmpPost->saveSettings();
  tmpPost->applaySettings();
  accept();
}


