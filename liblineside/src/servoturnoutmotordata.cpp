#include "tendril/pwmchannel.hpp"

#include "lineside/servoturnoutmotordata.hpp"

#include "lineside/servoturnoutmotor.hpp"

namespace Lineside {
  ServoTurnoutMotorData::ServoTurnoutMotorData() :
    PWItemData(),
    straight(),
    curved(),
    pwmChannelRequest() {}

  std::shared_ptr<PWItemModel> ServoTurnoutMotorData::Construct(Tendril::HardwareManager& hw,
								SoftwareManager& sw ) const {
    // Work around compiler warning/error
    this->UnusedSoftwareManager(sw);
    
    auto pwmChannelProvider = hw.pwmcProviderRegistrar.Retrieve(this->pwmChannelRequest.providerName);
    std::unique_ptr<Tendril::PWMChannel> servo;
    servo = pwmChannelProvider->GetHardware(this->pwmChannelRequest.idOnProvider,
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
    result->servo = std::move(servo);

    return result;
  }
}
