#pragma once

#include "pwitemdata.hpp"
#include "devicerequestdata.hpp"

namespace Lineside {
  class ServoTurnoutMotorData : public PWItemData {
  public:
    ServoTurnoutMotorData();

    unsigned int straight;
    unsigned int curved;
    DeviceRequestData pwmChannelRequest;

    virtual std::shared_ptr<PWItemModel> Construct( std::shared_ptr<HardwareManager> hw ) override;
  };
}
