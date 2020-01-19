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
    this->desiredState = wantedState;
    this->desiredFlash = wantedFlash;
    this->desiredFeather = wantedFeather;
    this->WakeController();
  }
}
