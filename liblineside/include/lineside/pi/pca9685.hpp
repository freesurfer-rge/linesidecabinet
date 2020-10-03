#pragma once

#include <string>

#include "lineside/pi/i2cdevice.hpp"

namespace Lineside {
  namespace Pi {
    class PCA9685 : public I2CDevice, public Lineside::PWMCProvider {
    public:
      const std::string refClockSetting = "referenceClock";
      const std::string pwmFreqSetting = "pwmFrequency";

      PCA9685(const std::string deviceName,
	      const std::map<std::string,std::string> settings,
	      std::unique_ptr<PiGPIOdpp::I2CDevice> i2cCommunicator);

      virtual void Register(HardwareManager& hwManager) override;

      virtual std::unique_ptr<Lineside::PWMChannel>
      GetHardware(const std::string& hardwareId,
		  const std::map<std::string,std::string>& settings) override;
    private:
      const unsigned char channels = 16;
      const int registerMODE1 = 0x00;
      const int registerPRESCALE = 0xfe;
      
      double referenceClock;
      double pwmFrequency;
      
      void CheckChannel(const unsigned char channel) const;
      unsigned char StartRegister(const unsigned char channel) const;
      unsigned char StopRegister(const unsigned char channel) const;

      void CommunicatePause() const;
    };
  }
}
