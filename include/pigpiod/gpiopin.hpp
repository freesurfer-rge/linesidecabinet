#pragma once

#include "pimanager.hpp"

#include "gpiomode.hpp"

namespace Lineside {
  namespace PiGPIOd {
    //! Class for controlling a GPIO pin
    class GPIOPin {
    public:
      GPIOPin(const std::shared_ptr<PiManager> owner,
	      const unsigned int pinId);

      int getPi() const {
	return this->pi->getId();
      }
      
      unsigned int getPin() const {
	return this->pin;
      }
      
      void SetMode(GPIOMode mode);

      void Write(const bool level);
      
    private:
      std::shared_ptr<PiManager> pi;
      const unsigned int pin;
    };
  }
}
