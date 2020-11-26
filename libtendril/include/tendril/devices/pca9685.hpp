#pragma once

#include <string>
#include <memory>
#include <set>

#include "tendril/tendriltypes.hpp"
#include "tendril/pwmchannel.hpp"
#include "tendril/hardwareprovider.hpp"
#include "tendril/i2ccommunicator.hpp"
#include "tendril/devices/device.hpp"

namespace Tendril::Devices {
  class PCA9685Channel;
  
  //! Class to represent a PCA9685 PWM channel array. Needs work
  /*!
    Represents a PCA9685 chip.
    This provides 16 hardware managed Pulse Width Modulation channels, managed over the I2C bus.
   */
  class PCA9685 : public Device, public HardwareProvider<PWMChannel> {
  public:
    const std::string refClockSetting = "referenceClock";
    const std::string pwmFreqSetting = "pwmFrequency";

    //! Construct an instance of the class
    /*!
      Note that I2CCommunicator is an abstract class.
      The implementing library must provide a pointer to a concrete object when invoking
      this constructor.

      @param deviceName The name to be used when registering with the HardwareManager
      @param settings Configuration settings
      @param i2cComms The means of communicating on the I2C bus. This pointer will not be valid when the constructor returns
     */
    PCA9685(const std::string deviceName,
	    const SettingsMap& settings,
	    std::unique_ptr<I2CCommunicator>& i2cComms);

    //! Register with the HardwareManager
    /*!
      Since the PCA9685 provides PWM channels, this will register this
      chip as such in the HardwareManager.
      
      @param hwManager The target HardwareManager
    */
    virtual void Register(HardwareManager& hwManager) override;

    //! Fetches a PWMChannel
    /*!
      @param hardwareId A string which must parse to a number 0-15
      @param settings Must be empty
    */
    virtual std::unique_ptr<PWMChannel>
    GetHardware(const std::string& hardwareId,
		const SettingsMap& settings) override;
    
  private:
    friend class PCA9685Channel;

    std::unique_ptr<I2CCommunicator> communicator;
    const unsigned char channels = 16;
    const int registerMODE1 = 0x00;
    const int registerPRESCALE = 0xfe;
    
    double referenceClock;
    double pwmFrequency;
    std::set<unsigned char> assignedChannels;
    
    void CheckChannel(const unsigned char channel) const;
    unsigned char StartRegister(const unsigned char channel) const;
    unsigned char StopRegister(const unsigned char channel) const;
    
    void SetChannelValue(const unsigned char channel,
			 const unsigned int start,
			 const unsigned int stop) const;
    
    void CommunicatePause() const;
  };
}
