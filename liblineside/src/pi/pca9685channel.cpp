#include "lineside/pi/pca9685channel.hpp"

namespace Lineside {
  namespace Pi {
    PCA9685Channel::PCA9685Channel( std::shared_ptr<PCA9685> controllerChip,
				    const unsigned char targetChannel ) :
      PWMChannel(),
      lastValue(16384),
      chip(controllerChip),
      channel(targetChannel) {}

    void PCA9685Channel::Set(const unsigned int value) {
      this->chip->SetChannelValue(this->channel, value);
      this->lastValue = value;
    }

    unsigned int PCA9685Channel::Get() const {
      return this->lastValue;
    }
  }
}
