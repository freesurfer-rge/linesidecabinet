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
      throw std::logic_error("Invalid chain length for 164");
    }
    this->state.resize(chainLength * this->PinsPerChip);
  }

    
  void
  DirectDriveSN74x164::Register(HardwareManager& hwManager) {
    // Get a shared pointer and navigate around the types
    auto ptr = this->shared_from_this();
    auto ptr164 = std::dynamic_pointer_cast<DirectDriveSN74x164>(ptr);
    hwManager.bopArrayProviderRegistrar.Register(this->name,
						 ptr164);

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


  void
  DirectDriveSN74x164::SetPinsAndSend(const std::map<unsigned int,bool>& pinUpdates) {
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
    
    // Reverse iterate to send the values
    for( auto rit=this->state.rbegin(); rit!=this->state.rend(); ++rit ) {
      this->dataPin->Set(*rit);
      std::this_thread::sleep_for(this->levelDelay);
      
      // Clock the value in
      this->clockPin->Set(true);
      std::this_thread::sleep_for(this->levelDelay);
      this->clockPin->Set(false);
    }
  }
  
}
