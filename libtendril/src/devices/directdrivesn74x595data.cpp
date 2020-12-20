#include "tendril/devices/directdrivesn74x595.hpp"

#include "tendril/devices/directdrivesn74x595data.hpp"

namespace Tendril::Devices {
  void
  DirectDriveSN74x595Data::ConstructAndRegister(HardwareManager& hw) {
    // Get the pins
    auto clock = hw.GetBOP(this->clockPin);
    auto data = hw.GetBOP(this->dataPin);
    auto latch = hw.GetBOP(this->latchPin);

    std::unique_ptr<BinaryOutputPin> clear;
    if( this->clearPin.providerName != Tendril::Devices::NotConnected ) {
      clear = hw.GetBOP(this->clearPin);
    }
    std::unique_ptr<BinaryOutputPin> enable;
    if( this->enablePin.providerName != Tendril::Devices::NotConnected ) {
      clear = hw.GetBOP(this->enablePin);
    }

    // Get the number of devices in the chain
    if( this->settings.size() != 1 ) {
      throw std::logic_error("DD595 should only have chainLength as a setting");
    }

    if( this->settings.count(this->chainLengthSetting) != 1 ) {
      throw KeyNotFoundException(this->chainLengthSetting);
    }
    std::string clString = this->settings.at(this->chainLengthSetting);
    unsigned int chainLength = std::stoul(clString);

    auto dd595 = std::make_shared<DirectDriveSN74x595>(this->name,
						       chainLength,
						       clock,
						       data,
						       latch,
						       enable,
						       clear);
    dd595->Register(hw);
  }
}
