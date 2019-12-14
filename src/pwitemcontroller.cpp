#include <stdexcept>
#include <sstream>

#include <boost/predef.h>

#include "linesideexceptions.hpp"
#include "pwitemmodel.hpp"

#include "pwitemcontroller.hpp"

namespace Lineside {
  PWItemController::~PWItemController() {

  }

  void PWItemController::Activate() {
    this->model->RegisterController(this->id.Get(),
				    this->shared_from_this());
    throw std::logic_error(__FUNCTION__);
  }

  void PWItemController::Run() {
    throw std::logic_error(__FUNCTION__);
  }

  void PWItemController::Deactivate() {
    this->state = ControllerState::Inactive;
    throw std::logic_error(__FUNCTION__);
  }

#if defined(BOOST_COMP_GNUC)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#elif defined(BOOST_COMP_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif
  void PWItemController::Notify(const unsigned int sourceId,
				const bool notification) {
    if( sourceId != this->id.Get() ) {
      throw ItemIdMismatchException( this->id, sourceId );
    }
    throw std::logic_error(__FUNCTION__);
  }
#if defined(BOOST_COMP_GNUC)
#pragma GCC diagnostic pop
#elif defined(BOOST_COMP_CLANG)
#pragma clange diagnostic pop
#endif
}
