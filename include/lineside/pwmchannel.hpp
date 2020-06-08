#pragma once

namespace Lineside {
  //! Abstraction for a Pulse Width Modulation channel
  class PWMChannel {
  public:
    virtual ~PWMChannel() {}

    virtual void Set(const unsigned int value) = 0;

    virtual unsigned int Get() const = 0;
  };
}
