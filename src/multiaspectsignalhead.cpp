#include "utility.hpp"

#include "multiaspectsignalhead.hpp"

namespace Lineside {
  void MultiAspectSignalHead::OnActivate() {
    throw std::logic_error(__PRETTY_FUNCTION__);
  }

  void MultiAspectSignalHead::OnDeactivate() {
    throw std::logic_error(__PRETTY_FUNCTION__);
  }

  std::chrono::milliseconds MultiAspectSignalHead::OnRun() {
    std::lock_guard<std::mutex> lockState(this->stateChangeMtx);
    throw std::logic_error(__PRETTY_FUNCTION__);
  }

  bool MultiAspectSignalHead::HaveStateChange() {
    throw std::logic_error(__PRETTY_FUNCTION__);
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
