#include "trackcircuitmonitor.hpp"

#include "utility.hpp"

namespace Lineside {
  void TrackCircuitMonitor::OnActivate() {}

  void TrackCircuitMonitor::OnDeactivate() {}

  std::chrono::milliseconds TrackCircuitMonitor::OnRun() {
     throw std::logic_error(__PRETTY_FUNCTION__);
  }

  bool TrackCircuitMonitor::HaveStateChange() {
    throw std::logic_error(__PRETTY_FUNCTION__);
  }

  bool TrackCircuitMonitor::GetState() const {
    LOCK_OR_THROW( bip, this->monitorPin );
    return bip->Get();
  }
}
