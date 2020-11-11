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
  class PCA9685 : public Device, public HardwareProvider<PWMChannel> {
  public:
    const std::string refClockSetting = "referenceClock";
    const std::string pwmFreqSetting = "pwmFrequency";

    PCA9685(const std::string deviceName,
	    const SettingsMap& settings,
	    std::unique_ptr<I2CCommunicator> i2cComms);

    virtual void Register(HardwareManager& hwManager) override;

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
