#include "trackcircuitmonitordata.hpp"
#include "trackcircuitmonitor.hpp"

#include "utility.hpp"

namespace Lineside {
  std::shared_ptr<PWItemModel>
  TrackCircuitMonitorData::Construct(HardwareManager& hw,
				     SoftwareManager& sw) const {
    auto bipProvider = hw.bipProviderRegistrar.Retrieve(this->inputPinRequest.controller);
    auto bip = bipProvider->GetHardware( this->inputPinRequest.controllerData,
					 this->inputPinRequest.settings );

    // Work around private constructor
    struct enabler : public TrackCircuitMonitor {
    public:
      friend class TrackCircuitMonitorData;
      enabler(const ItemId id) : TrackCircuitMonitor(id) {}
    };
    auto result = std::make_shared<enabler>(this->id);

    // Link up the input pin
    bip->RegisterListener(this->id.Get(), result);
    result->monitorPin = bip;

    // Get RTC client
    result->rtc = sw.GetRTCClient();

    return result;
  }
}
