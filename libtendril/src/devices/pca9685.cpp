#include <sstream>
#include <stdexcept>
#include <thread>

#include "tendril/devices/pca9685.hpp"
#include "tendril/devices/pca9685channel.hpp"

/*
  This needs work. Should look to the Adafruit
  library for the Arduino for inspiration
 */

namespace Tendril::Devices {
  PCA9685::PCA9685(const std::string deviceName,
		   const SettingsMap& settings,
		   std::unique_ptr<I2CCommunicator> i2cComms) :
    Device(deviceName),
    HardwareProvider(),
    communicator(std::move(i2cComms)),
    referenceClock(-1),
    pwmFrequency(-1),
    assignedChannels() {
    // Extract the settings
    if( settings.count(refClockSetting) != 1 ) {
      std::stringstream msg;
      msg << "Settings for PCA9685 did not contain " << refClockSetting;
      throw std::out_of_range(msg.str());
    }
    if( settings.count(pwmFreqSetting) != 1 ) {
      std::stringstream msg;
      msg << "Settings for PCA9685 did not contain " << pwmFreqSetting;
      throw std::out_of_range(msg.str());
    }
    
    this->referenceClock = std::stod(settings.at(refClockSetting));
    this->pwmFrequency = std::stod(settings.at(pwmFreqSetting));
    
    if( this->referenceClock <= 0 ) {
	throw std::out_of_range("referenceClock must be positive"); 
    }
    if( this->pwmFrequency <= 0 ) {
      throw std::out_of_range("pwmFrequency must be positive");
    }
    
    // Configure the chip
    const char enableValue = 0x20;
    this->communicator->WriteByte(PCA9685::registerMODE1, enableValue);
    this->CommunicatePause();
    
    // Enable change of the prescale value
    const char enablePrescaleValue = 0x10;
    this->communicator->WriteByte(PCA9685::registerMODE1, enablePrescaleValue);
    this->CommunicatePause();
    
    // Calculate prescale from Equation (1) of datasheet
    const unsigned char prescaleValue = round(this->referenceClock / 4096 / this->pwmFrequency) - 1;
    if( prescaleValue < 3 ) {
      throw std::invalid_argument("Calculated prescaleValue is less than 3");
    }
    
    // Set the prescale value
    this->communicator->WriteByte(PCA9685::registerPRESCALE, prescaleValue);
    this->CommunicatePause();
    
    // Put the chip back into the right mode
    this->communicator->WriteByte(PCA9685::registerMODE1, enableValue);
    
    // Set all 'start' registers to 0
    for( unsigned char c=0; c < PCA9685::channels; c++ ) {
      const unsigned char startRegister = this->StartRegister(c);
      this->communicator->WriteWord(startRegister, 0);
    }
  }
  
  void PCA9685::SetChannelValue(const unsigned char channel,
				const unsigned int start,
				const unsigned int stop) const {
    if( start >= 4096 ) {
      std::stringstream msg;
      msg << __FUNCTION__
	  << ": Invalid value " << start;
      throw std::out_of_range( msg.str().c_str() );
    }
    if( stop >= 4096 ) {
      std::stringstream msg;
      msg << __FUNCTION__
	  << ": Invalid value " << stop;
      throw std::out_of_range( msg.str().c_str() );
    }
    this->communicator->WriteWord(this->StartRegister(channel), start);
    this->communicator->WriteWord(this->StopRegister(channel), stop);
  }
  
  void PCA9685::Register(HardwareManager& hwManager) {
    // Get a shared pointer and navigate around the types
    auto ptr = this->shared_from_this();
    auto ptrPCA9685 = std::dynamic_pointer_cast<PCA9685>(ptr);
    hwManager.pwmcProviderRegistrar.Register(this->name,
					     ptrPCA9685);
  }
  
  std::unique_ptr<PWMChannel>
  PCA9685::GetHardware(const std::string& hardwareId,
		       const std::map<std::string,std::string>& settings) {
    if( settings.size() > 0 ) {
      std::stringstream msg;
      msg << __FUNCTION__
	  << ": Settings not supported for PCA9685";
      throw std::out_of_range(msg.str().c_str());
    }
    const unsigned int channel = std::stoul(hardwareId);
    if( channel >= PCA9685::channels ) {
      std::stringstream msg;
      msg << __FUNCTION__
	  << ": channelId " << hardwareId << " out of range";
      throw std::out_of_range(msg.str().c_str());
    }
    
    if( this->assignedChannels.count(channel) != 0 ) {
      std::stringstream msg;
      msg << __FUNCTION__
	  << ": channelId " << hardwareId << " already assigned";
      throw std::out_of_range(msg.str().c_str());
    }
    
    auto myself = std::dynamic_pointer_cast<PCA9685>(this->shared_from_this());
    auto result = std::make_unique<PCA9685Channel>(myself,channel);
    this->assignedChannels.insert(channel);
    return result;
  }
  
  unsigned char PCA9685::StartRegister(const unsigned char channel) const {
    this->CheckChannel(channel);
    
    return 0x06 + (channel*4);
  }
  
  unsigned char PCA9685::StopRegister(const unsigned char channel) const {
    this->CheckChannel(channel);
    
    return 0x08 + (channel*4);
  }
  
  void PCA9685::CheckChannel(const unsigned char channel) const {
    if( channel >= PCA9685::channels ) {
      std::stringstream msg;
      msg << "PCA9685 only has " << static_cast<unsigned int>(PCA9685::channels) << " channels";
      throw std::out_of_range("Only have 16 channels");
    }
  }
  
  void PCA9685::CommunicatePause() const {
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
  }
}
