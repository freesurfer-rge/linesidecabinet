#pragma once

#include "pimanager.hpp"

#include "gpiomode.hpp"

namespace Lineside {
  namespace PiGPIOd {
    //! Class for managing the GPIO on a Pi
    class GPIOManager {
    public:
      GPIOManager(const std::shared_ptr<PiManager> owner);

      void SetMode(const unsigned int gpio, GPIOMode mode);
      
    private:
      std::shared_ptr<PiManager> pi;
    };
  }
}
