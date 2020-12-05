#pragma once

#include <mutex>
#include <chrono>

#include "lineside/signalstate.hpp"
#include "lineside/signalaspect.hpp"
#include "lineside/signalflash.hpp"

#include "lineside/pwitemmodel.hpp"

namespace Lineside {
  //! Concept of a multiple aspect signal head
  /*!
    This does contain some data members, since it manages
    the current and desired states of the signal head.
    However, implementations are responsible for responding to these.
   */
  class MultiAspectSignalHead : public PWItemModel {
  public:
    const std::chrono::milliseconds FlashInterval = std::chrono::milliseconds(500);
    
    MultiAspectSignalHead(const ItemId id) :
      PWItemModel(id),
      stateChangeMtx(),
      currentState(SignalState::Red),
      desiredState(SignalState::Red),
      currentFlash(SignalFlash::Steady),
      desiredFlash(SignalFlash::Steady),
      currentFeather(0),
      desiredFeather(0),
      lastFlashStatus(true) {}

    virtual bool HaveStateChange() override;

    //! Set the desired state of the signal head
    virtual void SetState(const SignalState wantedState,
			  const SignalFlash wantedFlash,
			  const unsigned int wantedFeather);

    //! Return how many aspects are available
    virtual unsigned int GetAspectCount() const = 0;

    //! Return how many feathers are available
    virtual unsigned int GetFeatherCount() const = 0;
  protected:
    std::mutex stateChangeMtx;
    
    SignalState currentState;
    SignalState desiredState;
    SignalFlash currentFlash;
    SignalFlash desiredFlash;
    unsigned int currentFeather;
    unsigned int desiredFeather;

    bool lastFlashStatus;
  };
}
