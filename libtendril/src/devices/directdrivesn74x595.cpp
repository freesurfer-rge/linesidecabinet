#include <thread>
#include <sstream>

#include "tendril/keyexception.hpp"
#include "tendril/devices/directdrivesn74x595.hpp"

namespace Tendril::Devices {
  const std::chrono::microseconds DirectDriveSN74x595::DefaultLevelDelay = std::chrono::microseconds(10);
  const unsigned int DirectDriveSN74x595::PinsPerChip;
  
  DirectDriveSN74x595::DirectDriveSN74x595(const std::string deviceName,
					   const unsigned int chainLength,
					   std::unique_ptr<BinaryOutputPin>& clock,
					   std::unique_ptr<BinaryOutputPin>& data,
					   std::unique_ptr<BinaryOutputPin>& latch,
					   std::unique_ptr<BinaryOutputPin>& enable,
					   std::unique_ptr<BinaryOutputPin>& clear )
    : DirectDriveSIPOShiftRegister(deviceName, chainLength*PinsPerChip, clock, data),
      levelDelay(DirectDriveSN74x595::DefaultLevelDelay),
      latchPin(std::move(latch)),
      enablePin(std::move(enable)),
      clearPin(std::move(clear)) {
    if( this->clearPin ) {
      this->Reset();
    }
  }

  
  void
  DirectDriveSN74x595::EnableOutputs(bool enable) {
    if( this->enablePin ) {
      // Recall that it's an active low enable
      this->enablePin->Set(!enable);
    } else {
      throw std::logic_error("Enable pin is not set for 74x595");
    }
  }

  void
  DirectDriveSN74x595::Reset() {
    std::lock_guard<std::mutex> lck(this->updateMutex);

    if( this->clearPin ) {
      // The 'Clear' is active low
      this->clearPin->Set(false);
      std::this_thread::sleep_for(this->levelDelay);
      this->clearPin->Set(true);
    } else {
      throw std::logic_error("Reset pin is not set for 74x595");
    }
  }

  std::chrono::microseconds
  DirectDriveSN74x595::getLevelDelay() const {
    return this->levelDelay;
  }
  
  void DirectDriveSN74x595::setLevelDelay(const std::chrono::microseconds delay) {
    this->levelDelay = delay;
  }
  
  void DirectDriveSN74x595::BeforeSend() {
    this->latchPin->Set(false);
  }
  
  void DirectDriveSN74x595::AfterSend() {
    // Transfer the data to the output registers
    this->latchPin->Set(true);
    std::this_thread::sleep_for(this->getLevelDelay());
    this->latchPin->Set(false);
  }
}
