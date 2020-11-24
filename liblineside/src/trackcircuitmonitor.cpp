#include <sstream>
#include <boost/predef.h>

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
  
#if defined(BOOST_COMP_GNUC)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#elif defined(BOOST_COMP_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif
  void TrackCircuitMonitor::Notify(const bool& notification) {
    std::lock_guard<std::mutex> lockState(this->updateMtx);
    this->WakeController();
  }
#if defined(BOOST_COMP_GNUC)
#pragma GCC diagnostic pop
#elif defined(BOOST_COMP_CLANG)
#pragma clang diagnostic pop
#endif
}
