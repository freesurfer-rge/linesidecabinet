#include "pwitemmodel.hpp"

namespace Lineside {
  void PWItemModel::RegisterController(const unsigned int reqSrcId,
				       std::weak_ptr<Notifiable<bool>> target) {
    this->controllerNotifier.Register(reqSrcId, target);
  }

  void PWItemModel::WakeController() {
    this->controllerNotifier.Notify(true);
  }
}
