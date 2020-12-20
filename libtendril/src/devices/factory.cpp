#include "tendril/keyexception.hpp"

#include "tendril/devices/directdrivesn74x595.hpp"
#include "tendril/devices/directdrivesn74x595data.hpp"

#include "tendril/devices/factory.hpp"

namespace Tendril::Devices {
  std::unique_ptr<BinaryOutputPin>
  GetBOPFromRequest(const HardwareRequestData data,
		    HardwareManager& hw) {
    std::unique_ptr<BinaryOutputPin> result;

    auto provider = hw.bopProviderRegistrar.Retrieve(data.providerName);

    result = provider->GetHardware(data.idOnProvider, data.settings);
    
    return result;
  }

  void CreateAndRegisterDD595(const DirectDriveSN74x595Data& data595,
			      HardwareManager& hw) {
    // Set up the pins
    auto clock = GetBOPFromRequest(data595.clockPin, hw);
    auto data = GetBOPFromRequest(data595.dataPin, hw);
    auto latch = GetBOPFromRequest(data595.latchPin, hw);

    std::unique_ptr<BinaryOutputPin> clear;
    if( data595.clearPin.providerName != Tendril::Devices::NotConnected ) {
      clear = GetBOPFromRequest(data595.clearPin, hw);
    }
    std::unique_ptr<BinaryOutputPin> enable;
    if( data595.enablePin.providerName != Tendril::Devices::NotConnected ) {
      clear = GetBOPFromRequest(data595.enablePin, hw);
    }

    // Get the number of devices in the chain
    if( data595.settings.size() != 1 ) {
      throw std::logic_error("DD595 should only have chainLength as a setting");
    }

    if( data595.settings.count(data595.chainLengthSetting) != 1 ) {
      throw KeyNotFoundException(data595.chainLengthSetting);
    }

    unsigned int chainLength = std::stoul(data595.settings.at(data595.chainLengthSetting));

    auto dd595 = std::make_shared<DirectDriveSN74x595>(data595.name,
						       chainLength,
						       clock,
						       data,
						       latch,
						       enable,
						       clear);
    dd595->Register(hw);
  }
}
