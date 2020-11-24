#pragma once

#include "tendril/binaryinputpin.hpp"
#include "tendril/binaryoutputpin.hpp"


#include "pigpiodpp/gpiomode.hpp"
#include "pigpiodpp/gpioedge.hpp"
#include "pigpiodpp/gpiopull.hpp"

namespace PiGPIOdpp {
  class PiManager;
  
  //! Class for controlling a GPIO pin
  class GPIOPin : public Tendril::BinaryOutputPin, public Tendril::BinaryInputPin {
  public:
    GPIOPin(const std::shared_ptr<PiManager> owner,
	    const unsigned int pinId);
    
    ~GPIOPin();
    
    int getPi() const;
    
    unsigned int getPin() const {
	return this->pin;
    }
    
    void SetMode(const GPIOMode mode);
    
    virtual bool Get() const override;
    
    virtual void Set(const bool level) override;
    
    void SetPUDResistor(GPIOPull pull);
    
    void SetGlitchFilter(unsigned int steadyMicroseconds);
    
    void TriggerNotifications(int pi, unsigned user_gpio, unsigned level, uint32_t tick);
    
  private:
    std::shared_ptr<PiManager> pi;
    const unsigned int pin;
    
    int callBackId;

    void SetupCallback();

    void CancelCallback();
  };
}
