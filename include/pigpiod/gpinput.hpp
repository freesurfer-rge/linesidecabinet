#pragma once

#include "binaryinputpin.hpp"

#include "pigpiod/gpiopin.hpp"

namespace Lineside {
  namespace PiGPIOd {
    class GPInput : public BinaryInputPin {
    public:
      GPInput(std::unique_ptr<GPIOPin> piPin,
	      GPIOPull pull,
	      unsigned int glitchSteadyMicroseconds,
	      GPIOEdge callbackEdge);

      virtual bool Get() const override;

      void ReceiveUpdate(const bool level);
    private:
      std::unique_ptr<GPIOPin> pin;
    };
  }
}
