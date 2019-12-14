#include <stdexcept>
#include <sstream>

#include <boost/predef.h>

#include "linesideexceptions.hpp"
#include "pwitemmodel.hpp"

#include "pwitemcontroller.hpp"

namespace Lineside {
  PWItemController::~PWItemController() {
    this->Deactivate();
    if( this->t.joinable() ) {
      this->t.join();
    }
  }

  void PWItemController::Activate() {    
    this->model->RegisterController(this->id.Get(),
				    this->shared_from_this());

    // Spawn the thread using condition variable
    // to ensure it is active before this function exits
    std::unique_lock<std::mutex> lck(this->mtx);
    this->t = std::thread(&PWItemController::Run, this);

    while( this->state != ControllerState::Active ) {
      this->cv.wait(lck);
    }
    std::cout << __PRETTY_FUNCTION__ << ": Done";
  }

  void PWItemController::Run() {
    this->model->OnActivate();

    this->state = ControllerState::Active;
    this->cv.notify_one();
  }

  void PWItemController::Deactivate() {
    this->state = ControllerState::Inactive;
    this->cv.notify_one();
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
