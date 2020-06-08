#pragma once

#include "lineside/binaryoutputpin.hpp"

#include "pigpiodpp/gpiopin.hpp"

namespace Lineside {
  namespace Pi {
    class GPOutput : public BinaryOutputPin {
    public:
      GPOutput(std::unique_ptr<PiGPIOdpp::GPIOPin> piPin);

      virtual void Set(const bool level) override;

      virtual bool Get() const override;
      
    private:
      std::unique_ptr<PiGPIOdpp::GPIOPin> pin;
    };
  }
}
