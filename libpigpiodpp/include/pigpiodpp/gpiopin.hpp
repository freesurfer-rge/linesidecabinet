#pragma once

#include "tendril/binaryinputpin.hpp"
#include "tendril/binaryoutputpin.hpp"


#include "pigpiodpp/gpiomode.hpp"
#include "pigpiodpp/gpioedge.hpp"
#include "pigpiodpp/gpiopull.hpp"

namespace PiGPIOdpp {
  class PiManager;
  
  //! Class for controlling a GPIO pin
  /*!
    This class implements the BinaryInputPin and BinaryOutputPin concepts for the pigpiod library.
    It holds a pointer to the parent PiManager, in order to ensure that the pigpiod library remains active for its lifetime.
   */
  class GPIOPin : public Tendril::BinaryOutputPin, public Tendril::BinaryInputPin {
  public:
    GPIOPin(const std::shared_ptr<PiManager> owner,
	    const unsigned int pinId);
    
    ~GPIOPin();

    //! Get the id of the Pi being controlled
    int getPi() const;

    //! Get the id of this pin
    unsigned int getPin() const {
	return this->pin;
    }
    
    //! Sets whether this is an input or output pin
    void SetMode(const GPIOMode mode);

    //! Get the current level of the pin
    virtual bool Get() const override;

    //! Set the level of the pin
    virtual void Set(const bool level) override;

    //! Control the pull up/pull down resistor in this pin
    void SetPUDResistor(GPIOPull pull);

    //! Configure the glitch filter on the pin
    /*!
      Level changes will only be reported after they have been steady for the indicated number of microseconds.

      @param steadyMicroseconds Number of microseconds to require stable readings (max 300,000)
     */
    void SetGlitchFilter(unsigned int steadyMicroseconds);

    //! Used in the callback configuration from the pigpiod library
    void TriggerNotifications(int pi, unsigned user_gpio, unsigned level, uint32_t tick);
    
  private:
    std::shared_ptr<PiManager> pi;
    const unsigned int pin;
    
    int callBackId;

    void SetupCallback();

    void CancelCallback();
  };
}
