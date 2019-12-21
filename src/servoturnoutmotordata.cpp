#include "servoturnoutmotordata.hpp"

namespace Lineside {
  ServoTurnoutMotorData::ServoTurnoutMotorData() :
    PWItemData(),
    straight(),
    curved(),
    pwmChannelRequest() {}

  std::shared_ptr<PWItemModel> Construct( std::shared_ptr<HardwareManager> hw ) {
    throw std::logic_error(__PRETTY_FUNCTION__);
  }
}
