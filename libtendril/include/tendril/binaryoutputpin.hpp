#pragma once

namespace Tendril {
  //! Abstraction for a binary output pin
  class BinaryOutputPin {
  public:
    virtual ~BinaryOutputPin() {}

    //! Set the state of the pin
    virtual void Set(const bool level) = 0;
  };
}
