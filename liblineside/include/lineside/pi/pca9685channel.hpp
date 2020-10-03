#pragma once

#include <memory>

#include "lineside/pwmchannel.hpp"
#include "lineside/pi/pca9685.hpp"

namespace Lineside {
  namespace Pi {
    class PCA9685Channel : public PWMChannel {
    public:
      PCA9685Channel( std::shared_ptr<PCA9685> controllerChip,
		      const unsigned char targetChannel );
      
      virtual void Set(const unsigned int value) override;

      virtual unsigned int Get() const override;

    private:
      unsigned int lastValue;
      std::shared_ptr<PCA9685> chip;
      const unsigned char channel;
    };
  }
}
