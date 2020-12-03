#include "lineside/boparraymash.hpp"

namespace Lineside {
  void BOPArrayMASH::OnActivate() {
    this->markAllOff();
    this->pins->Set(this->aspects.at(SignalAspect::Red), true);
    this->pins->Update();
  }

  void BOPArrayMASH::OnDeactivate() {
    this->markAllOff();
    this->pins->Update();
  }

  std::chrono::milliseconds BOPArrayMASH::OnRun() {
    std::lock_guard<std::mutex> lockState(this->stateChangeMtx);
    
    if( this->HaveStateChange() || (this->currentFlash == SignalFlash::Flashing)) {
	this->markAllOff();
	
	this->setStateFromDesired();
	
	this->setFeatherFromDesired();
	
	this->currentState = this->desiredState;
	this->currentFlash = this->desiredFlash;
	this->currentFeather = this->desiredFeather;

	this->pins->Update();
      }
    return MultiAspectSignalHead::FlashInterval;
  }

  unsigned int BOPArrayMASH::GetAspectCount() const {
    return this->aspects.size();
  }

  unsigned int BOPArrayMASH::GetFeatherCount() const {
    return this->feathers.size();
  }

  void BOPArrayMASH::setStateFromDesired() {
    // Assumes that markAllOff() called previously, and that
    // SetState has prevented desiredState being invalid
    const bool isSteady = this->desiredFlash == SignalFlash::Steady;
    const bool nextOnOff = isSteady || this->lastFlashStatus;
    
    if( this->desiredState == SignalState::Red ) {
      this->pins->Set(this->aspects.at(SignalAspect::Red), nextOnOff);
    }
    if( this->desiredState == SignalState::Yellow ) {
      this->pins->Set(this->aspects.at(SignalAspect::Yellow1), nextOnOff);
    }
    if( this->desiredState == SignalState::DoubleYellow ) {
      this->pins->Set(this->aspects.at(SignalAspect::Yellow1), nextOnOff);
      this->pins->Set(this->aspects.at(SignalAspect::Yellow2), nextOnOff);
    }
    if( this->desiredState == SignalState::Green ) {
      this->pins->Set(this->aspects.at(SignalAspect::Green), nextOnOff);
    }

    this->lastFlashStatus = !this->lastFlashStatus;
  }

  
  void BOPArrayMASH::setFeatherFromDesired() {
    // Assumes that turnAllOff() called previously, and that
    // SetState has prevented desiredFeather being invalid
    if( this->desiredFeather > 0 ) {
      this->pins->Set(this->feathers.at(this->desiredFeather-1), true);
    }
  }
  
  void BOPArrayMASH::markAllOff() {
    const size_t nPins = this->GetAspectCount() + this->GetFeatherCount();
    for( size_t i=0; i<nPins; ++i ) {
      this->pins->Set(i, false);
    }
  }
}
