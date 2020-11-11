#pragma once

#include <memory>

#include "tendril/pwmchannel.hpp"
#include "tendril/devices/pca9685.hpp"

namespace Tendril::Devices {
  class PCA9685Channel : public PWMChannel {
  public:
    PCA9685Channel(std::shared_ptr<PCA9685> controllerChip,
		   const unsigned char targetChannel);
    
    virtual void Set(const unsigned int start,
		     const unsigned int stop) override;
  private:
    std::shared_ptr<PCA9685> controller;
    const unsigned char channel;
  };
}
