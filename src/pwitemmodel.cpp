#include "pwitemmodel.hpp"

namespace Lineside {
  void PWItemModel::RegisterController(const unsigned int reqSrcId,
				       std::weak_ptr<Notifiable<bool>> target) {
    this->controllerNotifier.Register(reqSrcId, target);
  }
}
