#include "utility.hpp"

#include "multiaspectsignalhead.hpp"

namespace Lineside {
  void MultiAspectSignalHead::OnActivate() {
    this->turnAllOff();
    LOCK_OR_THROW( r, this->red );
    r->Set(true);
  }

  void MultiAspectSignalHead::OnDeactivate() {
    throw std::logic_error(__PRETTY_FUNCTION__);
  }

  std::chrono::milliseconds MultiAspectSignalHead::OnRun() {
    std::lock_guard<std::mutex> lockState(this->stateChangeMtx);

    this->turnAllOff();

    this->setStateFromDesired();

    this->currentState = this->desiredState;
    this->currentFlash = this->desiredFlash;
    this->currentFeather = this->desiredFeather;
    return MultiAspectSignalHead::FlashInterval;
  }

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
      if( this->yellow1.expired() ) {
	auto stateString = this->buildStateString(wantedState, wantedFlash, wantedFeather);
	throw InvalidStateException(this->getId(), stateString);
      }
    }

    if( wantedState == SignalState::DoubleYellow ) {
      if( this->yellow2.expired() ) {
	auto stateString = this->buildStateString(wantedState, wantedFlash, wantedFeather);
	throw InvalidStateException(this->getId(), stateString);
      }
    }

    // Check on the feather
    if( wantedFeather > this->feathers.size() ) {
      auto stateString = this->buildStateString(wantedState, wantedFlash, wantedFeather);
      throw InvalidStateException(this->getId(), stateString);
    }
    
    this->desiredState = wantedState;
    this->desiredFlash = wantedFlash;
    this->desiredFeather = wantedFeather;
    this->WakeController();
  }

  std::string MultiAspectSignalHead::buildStateString(const SignalState state,
						      const SignalFlash flash,
						      const unsigned int feather) const {
    std::stringstream result;
    result << "{"
	   << state << ","
	   << flash << ","
	   << feather << "}";
    return result.str();
  }
  
  void MultiAspectSignalHead::turnAllOff() {
    // Always have Red and Green aspects
    LOCK_OR_THROW( g, this->green );
    g->Set(false);
    LOCK_OR_THROW( r, this->red );
    r->Set(false);
    
    // Check for Yellows
    if( !this->yellow1.expired() ) {
      LOCK_OR_THROW( y1, this->yellow1 );
      y1->Set(false);
    }
    if( !this->yellow2.expired() ) {
      LOCK_OR_THROW( y2, this->yellow2 );
      y2->Set(false);
    }
    
    // Check for feathers
    for( auto it=this->feathers.begin(); it!=this->feathers.end(); ++it ) {
      LOCK_OR_THROW( f, (*it) );
      f->Set(false);
    }
  }

  void MultiAspectSignalHead::setStateFromDesired() {
    // Assumes that turnAllOff() called previously, and that
    // SetState has prevented desiredState being invalid
    if( this->desiredState == SignalState::Red ) {
      LOCK_OR_THROW( r, this->red );
      r->Set(true);
    }
    if( this->desiredState == SignalState::Yellow ) {
      LOCK_OR_THROW( y1, this->yellow1 );
      y1->Set(true);
    }
    if( this->desiredState == SignalState::DoubleYellow ) {
      LOCK_OR_THROW( y1, this->yellow1 );
      y1->Set(true);
      LOCK_OR_THROW( y2, this->yellow2 );
      y2->Set(true);
    }
    if( this->desiredState == SignalState::Green ) {
      LOCK_OR_THROW( g, this->green );
      g->Set(true);
    }
  }
}
