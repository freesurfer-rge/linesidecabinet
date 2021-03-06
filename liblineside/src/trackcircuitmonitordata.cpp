#include "lineside/trackcircuitmonitordata.hpp"
#include "lineside/trackcircuitmonitor.hpp"

namespace Lineside {
  std::shared_ptr<PWItemModel>
  TrackCircuitMonitorData::Construct(Tendril::HardwareManager& hw,
				     SoftwareManager& sw) const {
    auto bipProvider = hw.bipProviderRegistrar.Retrieve(this->inputPinRequest.providerName);
    auto bip = bipProvider->GetHardware( this->inputPinRequest.idOnProvider,
					 this->inputPinRequest.settings );

    // Work around private constructor
    struct enabler : public TrackCircuitMonitor {
    public:
      friend class TrackCircuitMonitorData;
      enabler(const ItemId id, const TrackCircuitSensor sensor) : TrackCircuitMonitor(id, sensor) {}
    };
    auto result = std::make_shared<enabler>(this->id, this->sensor);
    
    // Link up the input pin
    bip->RegisterListener(result);
    result->monitorPin = std::move(bip);

    // Get RTC client
    result->rtc = sw.GetRTCClient();

    return result;
  }
}
