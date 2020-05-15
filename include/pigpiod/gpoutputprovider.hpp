#pragma once

#include "hardwareprovider.hpp"

#include "pigpiod/gpioprovider.hpp"
#include "pigpiod/gpoutput.hpp"


namespace Lineside {
  namespace PiGPIOd {
    class GPOutputProvider : HardwareProvider<BinaryOutputPin> {
    public:
      GPOutputProvider(std::shared_ptr<GPIOProvider> provider);

      virtual std::shared_ptr<BinaryOutputPin>
      GetHardware(const std::string& hardwareId,
		  const std::map<std::string,std::string>& settings) override;
    private:
      std::shared_ptr<GPIOProvider> gpioProvider;
    };
  }
}
