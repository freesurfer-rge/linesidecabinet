#pragma once

#include "lineside/pwitemdata.hpp"
#include "lineside/trackcircuitsensor.hpp"
#include "lineside/devicerequestdata.hpp"

namespace Lineside {
  //! Class to contain data specifying a TrackCircuitMonitor
  class TrackCircuitMonitorData : public PWItemData {
  public:
    TrackCircuitMonitorData() :
      PWItemData(),
      sensor(),
      inputPinRequest() {}

    TrackCircuitSensor sensor;
    DeviceRequestData inputPinRequest;

    virtual std::shared_ptr<PWItemModel> Construct(Tendril::HardwareManager& hw,
						   SoftwareManager& sw ) const override;
  };
}
