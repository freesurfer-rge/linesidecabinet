#pragma once

#include "hardwareprovider.hpp"

#include "pigpiod/gpioprovider.hpp"
#include "pigpiod/gpinput.hpp"

namespace Lineside {
  namespace PiGPIOd {
    class GPInputProvider : public HardwareProvider<BinaryInputPin> {
    public:
      GPInputProvider(std::shared_ptr<GPIOProvider> provider);

      virtual std::unique_ptr<BinaryInputPin>
      GetHardware(const std::string& hardwareId,
		  const std::map<std::string,std::string>& settings) override;
    private:
      std::shared_ptr<GPIOProvider> gpioProvider;
    };
  }
}
