#pragma once

#include "hardwareprovider.hpp"

#include "pi/gpioprovider.hpp"
#include "pi/gpinput.hpp"

namespace Lineside {
  namespace Pi {
    class GPInputProvider : public HardwareProvider<BinaryInputPin> {
    public:
      const std::string glitchSetting = "glitch";
      const std::string pudSetting = "pud";
      
      GPInputProvider(std::shared_ptr<GPIOProvider> provider);

      virtual std::unique_ptr<BinaryInputPin>
      GetHardware(const std::string& hardwareId,
		  const std::map<std::string,std::string>& settings) override;
    private:
      std::shared_ptr<GPIOProvider> gpioProvider;
    };
  }
}
