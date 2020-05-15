#include "servoturnoutmotordata.hpp"

#include "utility.hpp"
#include "servoturnoutmotor.hpp"

namespace Lineside {
  ServoTurnoutMotorData::ServoTurnoutMotorData() :
    PWItemData(),
    straight(),
    curved(),
    pwmChannelRequest() {}

  std::shared_ptr<PWItemModel> ServoTurnoutMotorData::Construct( std::shared_ptr<HardwareManager> hw,
								 std::shared_ptr<SoftwareManager> sw ) const {
    if( !hw ) {
      throw std::logic_error("Bad hw ptr");
    }
    if( !sw ) {
      throw std::logic_error("Bad sw ptr");
    }

    LOCK_OR_THROW( pwmChannelProvider,
		   hw->pwmcProviderRegistrar.Retrieve(this->pwmChannelRequest.controller) );
    std::shared_ptr<PWMChannel> servo;
    servo = pwmChannelProvider->GetHardware(this->pwmChannelRequest.controllerData,
					    this->pwmChannelRequest.settings);
    
    // Work around the private constructor
    struct enabler : public ServoTurnoutMotor {
    public:
      friend class ServoTurnoutMotorData;
      enabler(const ItemId id) : ServoTurnoutMotor(id) {}
    };
    auto result = std::make_shared<enabler>(this->id);
    result->pwmStraight = this->straight;
    result->pwmCurved = this->curved;
    result->servo = servo;

    return result;
  }
}
