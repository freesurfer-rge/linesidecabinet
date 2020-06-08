#pragma once

#include "lineside/pwitemdata.hpp"
#include "lineside/devicerequestdata.hpp"

namespace Lineside {
  class ServoTurnoutMotorData : public PWItemData {
  public:
    ServoTurnoutMotorData();

    unsigned int straight;
    unsigned int curved;
    DeviceRequestData pwmChannelRequest;

    virtual std::shared_ptr<PWItemModel> Construct(HardwareManager& hw,
						   SoftwareManager& sw) const override;
  };
}
