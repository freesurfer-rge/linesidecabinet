#include "servoturnoutmotordata.hpp"

namespace Lineside {
  ServoTurnoutMotorData::ServoTurnoutMotorData() :
    PWItemData(),
    straight(),
    curved(),
    pwmChannelRequest() {}

  std::shared_ptr<PWItemModel> ServoTurnoutMotorData::Construct( std::shared_ptr<HardwareManager> hw ) {
    if( !hw ) {
      throw std::logic_error("Bad hw ptr");
    }
    throw std::logic_error(__PRETTY_FUNCTION__);
  }
}
