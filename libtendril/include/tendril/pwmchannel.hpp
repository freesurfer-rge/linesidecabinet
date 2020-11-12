#pragma once

namespace Tendril {
  //! Abstraction for a Pulse Width Modulation channel
  class PWMChannel {
  public:
    virtual ~PWMChannel() {}

    virtual void Set(const unsigned int start, const unsigned int stop) = 0;
  };
}
