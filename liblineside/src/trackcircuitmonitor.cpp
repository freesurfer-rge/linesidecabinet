#include <sstream>

#include "lineside/trackcircuitmonitor.hpp"

namespace Lineside {
  void TrackCircuitMonitor::OnActivate() {}

  void TrackCircuitMonitor::OnDeactivate() {}

  std::chrono::milliseconds TrackCircuitMonitor::OnRun() {
    std::lock_guard<std::mutex> lockState(this->updateMtx);
    const bool notifyState = this->GetState();

    this->rtc->SendTrackCircuitNotification(this->getId(), notifyState);
    this->lastNotificationState = notifyState;
    
    return TrackCircuitMonitor::SleepRequest;
  }

  bool TrackCircuitMonitor::HaveStateChange() {
    std::lock_guard<std::mutex> lockState(this->updateMtx);
    return this->GetState() != this->lastNotificationState;
  }

  bool TrackCircuitMonitor::GetState() const {
    return this->monitorPin->Get() == ( Lineside::TrackCircuitSensor::OccupiedIsHigh == this->sensor );
  }

  void TrackCircuitMonitor::Notify(const unsigned int sourceId,
				   const bool notification) {
    std::lock_guard<std::mutex> lockState(this->updateMtx);
    if( ItemId(sourceId) != this->getId() ) {
      std::stringstream msg;
      msg << __PRETTY_FUNCTION__
	  << " has ItemId mismatch "
	  << " sourceId=" << ItemId(sourceId)
	  << " actualId=" << this->getId()
	  << " with state " << notification;
      throw std::logic_error(msg.str());
    }

    this->WakeController();
  }
}
