#include <sstream>

#include "trackcircuitmonitor.hpp"

#include "utility.hpp"

namespace Lineside {
  void TrackCircuitMonitor::OnActivate() {}

  void TrackCircuitMonitor::OnDeactivate() {}

  std::chrono::milliseconds TrackCircuitMonitor::OnRun() {
     throw std::logic_error(__PRETTY_FUNCTION__);
  }

  bool TrackCircuitMonitor::HaveStateChange() {
    return this->GetState() != this->lastNotificationState;
  }

  bool TrackCircuitMonitor::GetState() const {
    LOCK_OR_THROW( bip, this->monitorPin );
    return bip->Get();
  }

  void TrackCircuitMonitor::Notify(const unsigned int sourceId,
				   const bool notification) {
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
