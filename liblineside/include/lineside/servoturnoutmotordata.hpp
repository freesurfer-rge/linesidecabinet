#pragma once

#include "tendril/hardwarerequestdata.hpp"
#include "lineside/pwitemdata.hpp"

namespace Lineside {
  class ServoTurnoutMotorData : public PWItemData {
  public:
    ServoTurnoutMotorData();

    unsigned int straight;
    unsigned int curved;
    Tendril::HardwareRequestData pwmChannelRequest;

    virtual std::shared_ptr<PWItemModel> Construct(Tendril::HardwareManager& hw,
						   SoftwareManager& sw) const override;
  };
}
