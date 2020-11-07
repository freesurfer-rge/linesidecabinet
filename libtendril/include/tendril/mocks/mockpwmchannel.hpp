#pragma once

#include "tendril/pwmchannel.hpp"

namespace Tendril::Mocks {
  class MockPWMChannel : public PWMChannel {
  public:
    MockPWMChannel() :
      PWMChannel(),
      lastStart(),
      lastStop() {}
    
    virtual void Set(const unsigned int start,
		     const unsigned int stop) override;
    
    unsigned int lastStart;
    unsigned int lastStop;
  };
}
