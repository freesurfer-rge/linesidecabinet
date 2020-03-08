#pragma once

#include "pwitemdata.hpp"
#include "devicerequestdata.hpp"

namespace Lineside {
  class TrackCircuitMonitorData : public PWItemData {
  public:
    TrackCircuitMonitorData() :
      PWItemData(),
      inputPinRequest() {}

    DeviceRequestData inputPinRequest;

    virtual std::shared_ptr<PWItemModel> Construct( std::shared_ptr<HardwareManager> hw,
						    std::shared_ptr<SoftwareManager> sw ) const override;
  };
}
