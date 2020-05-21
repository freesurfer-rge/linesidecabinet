#pragma once

#include "pwitemdata.hpp"
#include "devicerequestdata.hpp"

namespace Lineside {
  //! Class to contain data specifying a TrackCircuitMonitor
  class TrackCircuitMonitorData : public PWItemData {
  public:
    TrackCircuitMonitorData() :
      PWItemData(),
      inputPinRequest() {}

    DeviceRequestData inputPinRequest;

    virtual std::shared_ptr<PWItemModel> Construct(HardwareManager& hw,
						   SoftwareManager& sw ) const override;
  };
}
