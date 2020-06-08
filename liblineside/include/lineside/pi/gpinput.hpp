#pragma once

#include "lineside/binaryinputpin.hpp"

#include "pigpiodpp/gpiopin.hpp"

namespace Lineside {
  namespace Pi {
    class GPInput : public BinaryInputPin {
    public:
      GPInput(std::unique_ptr<PiGPIOdpp::GPIOPin> piPin,
	      const PiGPIOdpp::GPIOPull pull,
	      const unsigned int glitchSteadyMicroseconds,
	      const PiGPIOdpp::GPIOEdge callBackEdge);

      virtual bool Get() const override;

      void ReceiveUpdate(const bool level);
    private:
      std::unique_ptr<PiGPIOdpp::GPIOPin> pin;
    };
  }
}
