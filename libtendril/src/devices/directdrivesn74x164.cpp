#include <thread>
#include <sstream>

#include "tendril/keyexception.hpp"


#include "tendril/devices/boparray164.hpp"
#include "tendril/devices/directdrivesn74x164.hpp"

namespace Tendril::Devices {
  const std::chrono::microseconds DirectDriveSN74x164::DefaultLevelDelay = std::chrono::microseconds(10);
  const unsigned int DirectDriveSN74x164::PinsPerChip;
  
  DirectDriveSN74x164::DirectDriveSN74x164(const std::string deviceName,
					   const unsigned int chainLength,
					   std::unique_ptr<BinaryOutputPin>& clock,
					   std::unique_ptr<BinaryOutputPin>& data,
					   std::unique_ptr<BinaryOutputPin>& clear)
    : DirectDriveSIPOShiftRegister(deviceName, chainLength*PinsPerChip, clock, data),
      levelDelay(DirectDriveSN74x164::DefaultLevelDelay),
      clearPin(std::move(clear)) {
    if( this->clearPin ) {
      this->Reset();
    }
  }
  
  void
  DirectDriveSN74x164::Reset() {
    std::lock_guard<std::mutex> lck(this->updateMutex);
    
    if( this->clearPin ) {
      // The 'Clear' is active low
      this->clearPin->Set(false);
      std::this_thread::sleep_for(this->levelDelay);
      this->clearPin->Set(true);
    } else {
      throw std::logic_error("Reset pin is not set for 74x164");
    }
  }

  std::chrono::microseconds
  DirectDriveSN74x164::getLevelDelay() const {
    return this->levelDelay;
  }

  void DirectDriveSN74x164::setLevelDelay(const std::chrono::microseconds delay) {
    this->levelDelay = delay;
  }

  void DirectDriveSN74x164::BeforeSend() {
    // Nothing to do
  }

  void DirectDriveSN74x164::AfterSend() {
    // Nothing to do
  }

  
}
