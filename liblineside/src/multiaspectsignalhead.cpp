#include "lineside/linesideexceptions.hpp"

#include "lineside/multiaspectsignalhead.hpp"

namespace Lineside {
  bool MultiAspectSignalHead::HaveStateChange() {
    bool changeState = this->desiredState != this->currentState;
    bool changeFlash = this->desiredFlash != this->currentFlash;
    bool changeFeather = this->desiredFeather != this->currentFeather;
    
    return changeState || changeFlash || changeFeather;
  }
  
  void MultiAspectSignalHead::SetState(const SignalState wantedState,
				       const SignalFlash wantedFlash,
				       const unsigned int wantedFeather ) {
    std::lock_guard<std::mutex> lockState(this->stateChangeMtx);
    
    // Checks on the aspects
    if( wantedState == SignalState::Yellow ) {
      if( this->GetAspectCount() < 3 ) {
	throw InvalidMASHStateException(this->getId(),
					wantedState,
					wantedFlash,
					wantedFeather);
      }
    }

    if( wantedState == SignalState::DoubleYellow ) {
      if( this->GetAspectCount() < 4 ) {
	throw InvalidMASHStateException(this->getId(), wantedState, wantedFlash, wantedFeather);
      }
    }

    // Check on the feather
    if( wantedFeather > this->GetFeatherCount() ) {
      throw InvalidMASHStateException(this->getId(), wantedState, wantedFlash, wantedFeather);
    }

    this->lastFlashStatus = true; // Make sure flashing starts with aspect on
    this->desiredState = wantedState;
    this->desiredFlash = wantedFlash;
    this->desiredFeather = wantedFeather;
    this->WakeController();
  }
}
