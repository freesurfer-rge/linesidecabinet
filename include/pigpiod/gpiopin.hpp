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
      //! Define the type of callback functions we accept
      /*!
	Callback functions are invoked with the level of the associated pin.
      */
      typedef std::function<void(bool)> CallBackFn;
      
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

      void SetCallback(GPIOEdge edge, CallBackFn f);

      void SetGlitchFilter(unsigned int steadyMicroseconds);

      void InvokeCallBack(int pi, unsigned user_gpio, unsigned level, uint32_t tick);
      
    private:
      std::shared_ptr<PiManager> pi;
      const unsigned int pin;

      CallBackFn callBack;
      int callBackId;
    };
  }
}
