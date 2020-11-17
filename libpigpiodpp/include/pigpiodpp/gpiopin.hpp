#pragma once

#include <functional>

#include "tendril/binaryinputpin.hpp"
#include "tendril/binaryoutputpin.hpp"

#include "pigpiodpp/pimanager.hpp"

#include "pigpiodpp/gpiomode.hpp"
#include "pigpiodpp/gpioedge.hpp"
#include "pigpiodpp/gpiopull.hpp"

namespace PiGPIOdpp {
  //! Class for controlling a GPIO pin
  class GPIOPin : public Tendril::BinaryOutputPin, public Tendril::BinaryInputPin {
  public:
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
    
    virtual bool Get() const override;
    
    virtual void Set(const bool level) override;
    
    void SetPUDResistor(GPIOPull pull);
    
    void SetGlitchFilter(unsigned int steadyMicroseconds);
    
    void TriggerNotifications(int pi, unsigned user_gpio, unsigned level, uint32_t tick);
    
  private:
    std::shared_ptr<PiManager> pi;
    const unsigned int pin;
    
    int callBackId;
  };
}
