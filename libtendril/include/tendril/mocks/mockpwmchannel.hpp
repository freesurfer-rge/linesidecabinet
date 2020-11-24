#pragma once

#include <vector>
#include <chrono>

#include "tendril/pwmchannel.hpp"
#include "tendril/tendriltypes.hpp"

namespace Tendril::Mocks {
  class MockPWMChannel : public PWMChannel {
  public:
    MockPWMChannel() :
      PWMChannel(),
      settings(),
      updates() {}
    
    virtual void Set(const unsigned int start,
		     const unsigned int stop) override;

    SettingsMap settings;

    std::vector<std::pair<unsigned int,unsigned int>> updates;
  };
}
