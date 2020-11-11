#include "tendril/devices/pca9685channel.hpp"

namespace Tendril::Devices {
  PCA9685Channel::PCA9685Channel(std::shared_ptr<PCA9685> controllerChip,
				 const unsigned char targetChannel)
    : PWMChannel(),
      controller(controllerChip),
      channel(targetChannel) {}

  void PCA9685Channel::Set(const unsigned int start,
			   const unsigned int stop) {
    this->controller->SetChannelValue(this->channel, start, stop);
  }
}
