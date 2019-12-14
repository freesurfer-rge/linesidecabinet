#include "pwitemmodel.hpp"

#include "pwitemcontroller.hpp"

namespace Lineside {
  PWItemController::PWItemController(std::shared_ptr<PWItemModel> pwim) :
    id(pwim->getId()),
    model(pwim),
    t(),
    mtx(),
    cv() {
    
  }

}
