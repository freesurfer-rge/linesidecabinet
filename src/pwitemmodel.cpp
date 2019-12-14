#include "pwitemmodel.hpp"

namespace Lineside {
  void PWItemModel::RegisterController(const unsigned int reqSrcId,
				       std::weak_ptr<Notifiable<bool>> target) {
    std::cout << __PRETTY_FUNCTION__ << ": BEGIN" << std::endl;
    this->controllerNotifier.Register(reqSrcId, target);
    std::cout << __PRETTY_FUNCTION__ << ": END" << std::endl;
  }
}
