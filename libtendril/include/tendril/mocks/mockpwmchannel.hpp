#pragma once

#include "tendril/pwmchannel.hpp"
#include "tendril/tendriltypes.hpp"

namespace Tendril::Mocks {
  class MockPWMChannel : public PWMChannel {
  public:
    MockPWMChannel() :
      PWMChannel(),
      lastStart(),
      lastStop(),
      settings() {}
    
    virtual void Set(const unsigned int start,
		     const unsigned int stop) override;
    
    unsigned int lastStart;
    unsigned int lastStop;

    SettingsMap settings;
  };
}
