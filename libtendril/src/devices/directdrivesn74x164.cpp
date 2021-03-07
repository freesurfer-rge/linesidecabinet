#include <thread>
#include <sstream>

#include "tendril/keyexception.hpp"


#include "tendril/devices/directdrivesn74x164.hpp"

namespace Tendril::Devices {
  DirectDriveSN74x164::DirectDriveSN74x164(const std::string deviceName,
					   const unsigned int chainLength,
					   std::unique_ptr<BinaryOutputPin>& clock,
					   std::unique_ptr<BinaryOutputPin>& data,
					   std::unique_ptr<BinaryOutputPin>& clear)
    : Device(deviceName),
      HardwareProvider(),
      levelDelay(DirectDriveSN74x164::DefaultLevelDelay),
      totalPins(chainLength * DirectDriveSN74x164::PinsPerChip),
      updateMutex(),
      clockPin(std::move(clock)),
      dataPin(std::move(data)),
      clearPin(std::move(clear)),
      state(),
      allocatedPins() {
    if( this->clearPin ) {
      this->Reset();
    }
    if( chainLength == 0 ) {
      throw std::logic_error("Invalid chain length for 595");
    }
    this->state.resize(chainLength * this->PinsPerChip);
  }
  
}
