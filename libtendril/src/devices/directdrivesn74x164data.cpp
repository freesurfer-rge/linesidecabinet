#include "tendril/devices/directdrivesn74x164.hpp"

#include "tendril/devices/directdrivesn74x164data.hpp"

namespace Tendril::Devices {
  void
  DirectDriveSN74x164Data::ConstructAndRegister(HardwareManager& hw) {
    // Get the pins
    auto clock = hw.GetBOP(this->clockPin);
    auto data = hw.GetBOP(this->dataPin);

    std::unique_ptr<BinaryOutputPin> clear;
    if( this->clearPin.providerName != Tendril::Devices::NotConnected ) {
      clear = hw.GetBOP(this->clearPin);
    }

    // Get the number of devices in the chain
    if( this->settings.size() != 1 ) {
      throw std::logic_error("DD164 should only have chainLength as a setting");
    }

    if( this->settings.count(this->chainLengthSetting) != 1 ) {
      throw KeyNotFoundException(this->chainLengthSetting);
    }
    std::string clString = this->settings.at(this->chainLengthSetting);
    unsigned int chainLength = std::stoul(clString);

    auto dd164 = std::make_shared<DirectDriveSN74x164>(this->name,
						       chainLength,
						       clock,
						       data,
						       clear);
    dd164->Register(hw);
  }
}
