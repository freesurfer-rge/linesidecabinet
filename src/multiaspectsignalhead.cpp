#include "utility.hpp"

#include "multiaspectsignalhead.hpp"

namespace Lineside {
  void MultiAspectSignalHead::OnActivate() {
    LOCK_OR_THROW( g, this->green );
    g->Set(false);
    LOCK_OR_THROW( r, this->red );
    r->Set(true);
    
    if( !this->yellow1.expired() ) {
      LOCK_OR_THROW( y1, this->yellow1 );
      y1->Set(false);
    }
    if( !this->yellow2.expired() ) {
      LOCK_OR_THROW( y2, this->yellow2 );
      y2->Set(false);
    }

    for( auto it=this->feathers.begin(); it!=this->feathers.end(); ++it ) {
      LOCK_OR_THROW( f, (*it) );
      f->Set(false);
    }
  }

  void MultiAspectSignalHead::OnDeactivate() {
    throw std::logic_error(__PRETTY_FUNCTION__);
  }

  std::chrono::milliseconds MultiAspectSignalHead::OnRun() {
    std::lock_guard<std::mutex> lockState(this->stateChangeMtx);
    throw std::logic_error(__PRETTY_FUNCTION__);
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

}
