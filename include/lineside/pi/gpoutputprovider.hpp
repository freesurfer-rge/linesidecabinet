#pragma once

#include "lineside/hardwareprovider.hpp"

#include "lineside/pi/gpioprovider.hpp"
#include "lineside/pi/gpoutput.hpp"

namespace Lineside {
  namespace Pi {
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
