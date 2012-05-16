#include "qiwipost.h"

namespace Qiwi{
namespace Internal {
  class QiwiPostPrivate {
  public:

  };
}
}

using namespace Qiwi;
using namespace Qiwi::Internal;

QiwiPost::QiwiPost(QObject *parent)
  : QObject(parent), d(new QiwiPostPrivate){
}

QiwiPost::~QiwiPost() {
  delete d;
}
