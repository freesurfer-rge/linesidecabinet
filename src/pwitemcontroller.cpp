#include <stdexcept>
#include <sstream>

#include <boost/predef.h>

#include "linesideexceptions.hpp"
#include "pwitemmodel.hpp"

#include "pwitemcontroller.hpp"

namespace Lineside {
  std::shared_ptr<PWItemController> PWItemController::Construct(std::shared_ptr<PWItemModel> pwim) {
    std::shared_ptr<PWItemController> result;

    // Work around the private constructor of PWItemController
    struct enabler : public PWItemController {};
    
    result = std::make_shared<enabler>();
    result->id = pwim->getId();
    result->model = pwim;
    result->model->RegisterController(result->id.Get(), result);

    return result;
  }
  
  PWItemController::~PWItemController() {
    this->Deactivate();
    if( this->t.joinable() ) {
      this->t.join();
    }
  }

  void PWItemController::Activate() {
    if( this->state != ControllerState::Constructed ) {
      std::stringstream msg;
      msg << "Improper Activate() call on " << this->id;
      throw std::logic_error(msg.str());
    }

    // Spawn the thread using condition variable
    // to ensure it is active before this function exits
    std::unique_lock<std::mutex> lck(this->mtx);
    this->t = std::thread(&PWItemController::Run, this);

    while( this->state != ControllerState::Active ) {
      this->cv.wait(lck);
    }
  }

  void PWItemController::Run() {
    // First, unblock the thread which spawned the signal
    {
      // The mutex ensures that the spawning thread has
      // reached the cv.wait()
      std::lock_guard<std::mutex> lg(this->mtx);
      this->model->OnActivate();
      this->state = ControllerState::Active;
    }
    this->cv.notify_one();
    
    std::chrono::milliseconds nextWait = this->MaximumWaitSeconds;
    do {
      std::unique_lock<std::mutex> lck(this->mtx);
      
      nextWait = this->model->OnRun();
      if( nextWait > this->MaximumWaitSeconds ) {
	nextWait = this->MaximumWaitSeconds;
      }
      
      this->cv.wait_for( lck, nextWait, [this](){ return this->CheckWakeUp(); } );
    } while( this->state == ControllerState::Active );

    this->model->OnDeactivate();
  }

  void PWItemController::Deactivate() {
    this->state = ControllerState::Inactive;
    this->cv.notify_one();
  }

  void PWItemController::Notify(const unsigned int sourceId,
				const bool notification) {
    if( !notification ) {
      throw std::logic_error("Unexpected notification to PWItemController::Notify");
    }
    if( sourceId != this->id.Get() ) {
      throw ItemIdMismatchException( this->id, sourceId );
    }
    this->cv.notify_one();
  }

  bool PWItemController::CheckWakeUp() const {
    bool shouldWake = (this->state != ControllerState::Active);

    shouldWake = shouldWake || this->model->HaveStateChange();

    return shouldWake;
  }
}
