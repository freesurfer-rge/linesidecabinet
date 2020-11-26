#pragma once

#include <memory>

#include "tendril/pwmchannel.hpp"
#include "tendril/devices/pca9685.hpp"

namespace Tendril::Devices {
  //! Implementation of PWMChannel for the PCA9685 chip
  class PCA9685Channel : public PWMChannel {
  public:
    //! Create an instance of the class
    /*!
      @param controllerChip The instance of the chip controlling this channel
      @param targetChannel The channel on the chip (must be 0-15)
    */
    PCA9685Channel(std::shared_ptr<PCA9685> controllerChip,
		   const unsigned char targetChannel);

    //! Set the start and stop values on the channel
    virtual void Set(const unsigned int start,
		     const unsigned int stop) override;
  private:
    std::shared_ptr<PCA9685> controller;
    const unsigned char channel;
  };
}
