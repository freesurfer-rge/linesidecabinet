#include <thread>
#include <sstream>

#include "tendril/keyexception.hpp"

#include "tendril/devices/boparraysiposr.hpp"
#include "tendril/devices/directdrivesiposhiftregister.hpp"


namespace Tendril::Devices {
  DirectDriveSIPOShiftRegister::DirectDriveSIPOShiftRegister(const std::string deviceName,
							     const unsigned int pinsInChain,
							     std::unique_ptr<BinaryOutputPin>& clock,
							     std::unique_ptr<BinaryOutputPin>& data)
    : Device(deviceName),
      HardwareProvider(),
      pinsInChain(pinsInChain),
      updateMutex(),
      clockPin(std::move(clock)),
      dataPin(std::move(data)),
      state(),
      allocatedPins() {
    if( this->pinsInChain == 0 ) {
      throw std::logic_error("Invalid chain length for DirectDriveSIPOShiftRegister");
    }
    this->state.resize(this->pinsInChain);
  }

  void
  DirectDriveSIPOShiftRegister::Register(HardwareManager& hwManager) {
    // Get a shared pointer and navigate around the types
    auto ptr = this->shared_from_this();
    auto ptrSIPOsr = std::dynamic_pointer_cast<DirectDriveSIPOShiftRegister>(ptr);
    hwManager.bopArrayProviderRegistrar.Register(this->name,
						 ptrSIPOsr);

  }

  std::unique_ptr<BOPArray>
  DirectDriveSIPOShiftRegister::GetHardware(const std::string& hardwareId,
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
      if( p >= this->pinsInChain ) {
	std::stringstream msg;
	msg << "Pin " << p << " too large for " << hardwareId;
	throw std::logic_error(msg.str());
      }
      this->allocatedPins.insert(p);
    }
    
    auto myself = std::dynamic_pointer_cast<DirectDriveSIPOShiftRegister>(this->shared_from_this());
    auto result = std::make_unique<BOPArraySIPOSR>(myself, pinList);

    return result;
  }

  void
  DirectDriveSIPOShiftRegister::SetPinsAndSend(const std::map<unsigned int,bool>& pinUpdates) {
    std::lock_guard<std::mutex> lck(this->updateMutex);
    
    // Update the state vector
    for( auto it : pinUpdates ) {
      if( this->allocatedPins.count(it.first) != 1 ) {
	throw std::logic_error("SetPinsAndSend pin not allocated");
      }
      
      this->state.at(it.first) = it.second;
    }
    
    // Have child class prepare
    this->BeforeSend();
    // Make sure the clock pin is low
    this->clockPin->Set(false);
    
    // Reverse iterate to send the values
    for( auto rit=this->state.rbegin(); rit!=this->state.rend(); ++rit ) {
      this->dataPin->Set(*rit);
      std::this_thread::sleep_for(this->getLevelDelay());
      
      // Clock the value in
      this->clockPin->Set(true);
      std::this_thread::sleep_for(this->getLevelDelay());
      this->clockPin->Set(false);
    }

    // Any required operations after the send
    this->AfterSend();
  }
}
