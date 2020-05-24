#pragma once

#include <functional>

#include "pimanager.hpp"

#include "gpiomode.hpp"
#include "gpioedge.hpp"

namespace Lineside {
  namespace PiGPIOd {
    //! Class for controlling a GPIO pin
    class GPIOPin {
    public:
      typedef std::function<void(int,unsigned int,unsigned int, uint32_t)> CallBackFn;
      
      GPIOPin(const std::shared_ptr<PiManager> owner,
	      const unsigned int pinId);

      ~GPIOPin();

      int getPi() const {
	return this->pi->getId();
      }
      
      unsigned int getPin() const {
	return this->pin;
      }
      
      void SetMode(GPIOMode mode);

      bool Read() const;
      
      void Write(const bool level);

      int SetCallback(GPIOEdge edge, CallBackFn f);
      
    private:
      std::shared_ptr<PiManager> pi;
      const unsigned int pin;

      int callBackId;
    };
  }
}
