#pragma once

#include "hardwareprovider.hpp"

#include "pigpiod/gpioprovider.hpp"
#include "pigpiod/gpoutput.hpp"


namespace Lineside {
  namespace PiGPIOd {
    class GPOutputProvider : public HardwareProvider<BinaryOutputPin> {
    public:
      GPOutputProvider(std::shared_ptr<GPIOProvider> provider);

      virtual std::unique_ptr<BinaryOutputPin>
      GetHardware(const std::string& hardwareId,
		  const std::map<std::string,std::string>& settings) override;
    private:
      std::shared_ptr<GPIOProvider> gpioProvider;
    };
  }
}
