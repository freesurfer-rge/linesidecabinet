#pragma once

namespace Tendril {
  //! Abstraction for a Pulse Width Modulation channel
  class PWMChannel {
  public:
    virtual ~PWMChannel() {}

    //! Set the pulse on the channel
    /*!
      The exact meanings ascribed to the parameters a defined by the implementation

      @param start When to start the pulse
      @param stop When to stop the pulse
    */
    virtual void Set(const unsigned int start, const unsigned int stop) = 0;
  };
}
