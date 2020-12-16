#include <thread>
#include <sstream>

#include "tendril/keyexception.hpp"

#include "tendril/devices/boparray595.hpp"
#include "tendril/devices/directdrivesn74x595.hpp"

namespace Tendril::Devices {
  DirectDriveSN74x595::DirectDriveSN74x595(const std::string deviceName,
					   const unsigned int chainLength,
					   std::unique_ptr<BinaryOutputPin>& clock,
					   std::unique_ptr<BinaryOutputPin>& data,
					   std::unique_ptr<BinaryOutputPin>& latch,
					   std::unique_ptr<BinaryOutputPin>& enable,
					   std::unique_ptr<BinaryOutputPin>& clear )
    : Device(deviceName),
      HardwareProvider(),
      levelDelay(DirectDriveSN74x595::DefaultLevelDelay),
      updateMutex(),
      clockPin(std::move(clock)),
      dataPin(std::move(data)),
      latchPin(std::move(latch)),
      enablePin(std::move(enable)),
      clearPin(std::move(clear)),
      totalPins(chainLength * DirectDriveSN74x595::PinsPerChip),
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
					   
  
  void
  DirectDriveSN74x595::Register(HardwareManager& hwManager) {
    // Get a shared pointer and navigate around the types
    auto ptr = this->shared_from_this();
    auto ptr595 = std::dynamic_pointer_cast<DirectDriveSN74x595>(ptr);
    hwManager.bopArrayProviderRegistrar.Register(this->name,
						 ptr595);

  }

  std::unique_ptr<BOPArray>
  DirectDriveSN74x595::GetHardware(const std::string& hardwareId,
				   const SettingsMap& settings) {
    // Convert the settings to an ordered list of strings
    auto pinStringList = BOPArray::ExtractPinList(settings);
    std::vector<unsigned int> pinList;
    for(auto s : pinStringList) {
      unsigned int nxt = std::stoul(s);
      pinList.push_back(nxt);
    }

    // Update the list of pins already given out
    for( unsigned int p : pinList ) {
      if( allocatedPins.count(p) != 0 ) {
	throw DuplicateKeyException(std::to_string(p));
      }
      if( p >= this->totalPins ) {
	std::stringstream msg;
	msg << "Pin " << p << " too large for " << hardwareId;
	throw std::logic_error(msg.str());
      }
      this->allocatedPins.insert(p);
    }
    
    auto myself = std::dynamic_pointer_cast<DirectDriveSN74x595>(this->shared_from_this());
    auto result = std::make_unique<BOPArray595>(myself, pinList);

    return result;
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
