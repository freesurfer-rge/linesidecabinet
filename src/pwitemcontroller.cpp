#include <stdexcept>
#include "pwitemmodel.hpp"

#include "pwitemcontroller.hpp"

namespace Lineside {
  PWItemController::PWItemController(std::shared_ptr<PWItemModel> pwim) :
    id(pwim->getId()),
    model(pwim),
    state(ControllerState::Constructed),
    t(),
    mtx(),
    cv() {
    this->model->RegisterController(this->id.Get(),
				    this->shared_from_this());
  }

  PWItemController::~PWItemController() {

  }

  void PWItemController::Activate() {
    throw std::logic_error(__FUNCTION__);
  }

  void PWItemController::Run() {
    throw std::logic_error(__FUNCTION__);
  }

  void PWItemController::Deactivate() {
    this->state = ControllerState::Inactive;
    throw std::logic_error(__FUNCTION__);
  }
}
