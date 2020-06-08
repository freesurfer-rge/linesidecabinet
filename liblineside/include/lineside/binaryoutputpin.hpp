#pragma once

namespace Lineside {
  //! Abstraction for a binary output pin
  class BinaryOutputPin {
  public:
    virtual ~BinaryOutputPin() {}

    //! Set the pin's state to true (high) or false (low)
    virtual void Set(const bool level) = 0;

    //! Get the current state of the pin
    virtual bool Get() const = 0;

    //! Convenience function to set pin to true
    void TurnOn() {
      this->Set(true);
    }

    //! Convenience function to set pin to false
    void TurnOff() {
      this->Set(false);
    }
  };
}
