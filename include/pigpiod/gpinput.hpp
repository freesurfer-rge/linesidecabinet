#pragma once

#include "binaryinputpin.hpp"

#include "pigpiod/gpiopin.hpp"

namespace Lineside {
  namespace PiGPIOd {
    class GPInput : public BinaryInputPin {
    public:
      GPInput(std::unique_ptr<GPIOPin> piPin,
	      const GPIOPull pull,
	      const unsigned int glitchSteadyMicroseconds,
	      const GPIOEdge callBackEdge);

      virtual bool Get() const override;

      void ReceiveUpdate(const bool level);
    private:
      std::unique_ptr<GPIOPin> pin;
    };
  }
}
