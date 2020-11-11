#pragma once

#include "tendril/mocks/mockbop.hpp"
#include "tendril/mocks/mockbip.hpp"
#include "tendril/mocks/mockboparray.hpp"
#include "tendril/mocks/mockpwmchannel.hpp"

#include "tendril/mocks/mockboparrayprovider.hpp"
#include "tendril/mocks/mockhardwareprovider.hpp"

#include "tendril/hardwaremanager.hpp"

namespace Tendril::Mocks {
  class MockHardwareManager : public HardwareManager {
  public:
    const std::string BIPProviderId = "BIP";
    const std::string BOPProviderId = "BOP";
    const std::string BOPArrayProviderId = "BOPArray";
    const std::string PWMCProviderId = "PWMC";
    
    MockHardwareManager();

    std::shared_ptr<MockHardwareProvider<BinaryInputPin, MockBIP>> bipProvider;
    std::shared_ptr<MockHardwareProvider<BinaryOutputPin, MockBOP>> bopProvider;
    std::shared_ptr<MockBOPArrayProvider> bopArrayProvider;
    std::shared_ptr<MockHardwareProvider<PWMChannel, MockPWMChannel>> pwmChannelProvider;
  };
}
