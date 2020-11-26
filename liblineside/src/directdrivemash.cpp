#include "lineside/linesideexceptions.hpp"

#include "lineside/directdrivemash.hpp"

namespace Lineside {
  void DirectDriveMASH::OnActivate() {
    this->turnAllOff();
    this->red->Set(true);
  }

  void DirectDriveMASH::OnDeactivate() {
    this->turnAllOff();
  }

  std::chrono::milliseconds DirectDriveMASH::OnRun() {
    std::lock_guard<std::mutex> lockState(this->stateChangeMtx);

    if( this->HaveStateChange() || (this->currentFlash == SignalFlash::Flashing)) {
	this->turnAllOff();
	
	this->setStateFromDesired();
	
	this->setFeatherFromDesired();
	
	this->currentState = this->desiredState;
	this->currentFlash = this->desiredFlash;
	this->currentFeather = this->desiredFeather;
      }
    return DirectDriveMASH::FlashInterval;
  }

  bool DirectDriveMASH::HaveStateChange() {
    bool changeState = this->desiredState != this->currentState;
    bool changeFlash = this->desiredFlash != this->currentFlash;
    bool changeFeather = this->desiredFeather != this->currentFeather;

    return changeState || changeFlash || changeFeather;
  }

  void DirectDriveMASH::SetState(const SignalState wantedState,
				 const SignalFlash wantedFlash,
				 const unsigned int wantedFeather ) {
    std::lock_guard<std::mutex> lockState(this->stateChangeMtx);
    
    // Checks on the aspects
    if( wantedState == SignalState::Yellow ) {
      if( !this->yellow1 ) {
	auto stateString = this->buildStateString(wantedState, wantedFlash, wantedFeather);
	throw InvalidMASHStateException(this->getId(), wantedState, wantedFlash, wantedFeather);
      }
    }

    if( wantedState == SignalState::DoubleYellow ) {
      if( !this->yellow2 ) {
	auto stateString = this->buildStateString(wantedState, wantedFlash, wantedFeather);
	throw InvalidMASHStateException(this->getId(), wantedState, wantedFlash, wantedFeather);
      }
    }

    // Check on the feather
    if( wantedFeather > this->feathers.size() ) {
      auto stateString = this->buildStateString(wantedState, wantedFlash, wantedFeather);
      throw InvalidMASHStateException(this->getId(), wantedState, wantedFlash, wantedFeather);
    }

    this->lastFlashStatus = true; // Make sure flashing starts with aspect on
    this->desiredState = wantedState;
    this->desiredFlash = wantedFlash;
    this->desiredFeather = wantedFeather;
    this->WakeController();
  }

  std::string DirectDriveMASH::buildStateString(const SignalState state,
						const SignalFlash flash,
						const unsigned int feather) const {
    std::stringstream result;
    result << "{"
	   << state << ","
	   << flash << ","
	   << feather << "}";
    return result.str();
  }
  
  void DirectDriveMASH::turnAllOff() {
    // Always have Red and Green aspects
    this->green->Set(false);
    this->red->Set(false);
    
    // Check for Yellows
    if( this->yellow1 ) {
      this->yellow1->Set(false);
    }
    if( this->yellow2 ) {
      this->yellow2->Set(false);
    }
    
    // Check for feathers
    for( auto it=this->feathers.begin(); it!=this->feathers.end(); ++it ) {
      (*it)->Set(false);
    }
  }

  void DirectDriveMASH::setStateFromDesired() {
    // Assumes that turnAllOff() called previously, and that
    // SetState has prevented desiredState being invalid
    const bool isSteady = this->desiredFlash == SignalFlash::Steady;
    const bool nextOnOff = isSteady || this->lastFlashStatus;
    
    if( this->desiredState == SignalState::Red ) {
      this->red->Set(nextOnOff);
    }
    if( this->desiredState == SignalState::Yellow ) {
      this->yellow1->Set(nextOnOff);
    }
    if( this->desiredState == SignalState::DoubleYellow ) {
      this->yellow1->Set(nextOnOff);
      this->yellow2->Set(nextOnOff);
    }
    if( this->desiredState == SignalState::Green ) {
      this->green->Set(nextOnOff);
    }

    this->lastFlashStatus = !this->lastFlashStatus;
  }

  void DirectDriveMASH::setFeatherFromDesired() {
    // Assumes that turnAllOff() called previously, and that
    // SetState has prevented desiredFeather being invalid
    if( this->desiredFeather > 0 ) {
      this->feathers.at(this->desiredFeather-1)->Set(true);
    }
  }
}
