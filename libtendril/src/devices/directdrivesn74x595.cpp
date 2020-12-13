#include <thread>

#include "tendril/devices/directdrivesn74x595.hpp"

namespace Tendril::Devices {
  void
  DirectDriveSN74x595::Register(HardwareManager& hwManager) {
    // Get a shared pointer and navigate around the types
    auto ptr = this->shared_from_this();
    auto ptr595 = std::dynamic_pointer_cast<DirectDriveSN74x595>(ptr);
    hwManager.bopArrayProviderRegistrar.Register(this->name,
						 ptr595);

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

  void
  DirectDriveSN74x595::SetPinsAndSend(const std::map<unsigned int,bool>& pinUpdates) {
    std::lock_guard<std::mutex> lck(this->updateMutex);
    
    // Update the state vector
    for( auto it : pinUpdates ) {
      if( this->allocatedPins.count(it.first) != 1 ) {
	throw std::logic_error("SetPinsAndSend pin not allocated");
      }

      this->state.at(it.first) = it.second;
    }

    // Make sure the clock pin and latch pins are low
    this->clockPin->Set(false);
    this->latchPin->Set(false);
    
    // Reverse iterate to send the values
    for( auto rit=this->state.rbegin(); rit!=this->state.rend(); ++rit ) {
      this->dataPin->Set(*rit);
      std::this_thread::sleep_for(this->levelDelay);

      // Clock the value in
      this->clockPin->Set(true);
      std::this_thread::sleep_for(this->levelDelay);
      this->clockPin->Set(false);
    }

    // Transfer the data to the output registers
    this->latchPin->Set(true);
    std::this_thread::sleep_for(this->levelDelay);
    this->latchPin->Set(false);
  }
}
