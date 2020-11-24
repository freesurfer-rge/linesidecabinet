#pragma once

#include <memory>

#include "tendril/hardwaremanager.hpp"

namespace Tendril::Mocks {
  std::shared_ptr<HardwareManager> GetMockHardwareManager();
  
  const std::string BIPProviderId = "MockBIP";
  const std::string BOPProviderId = "MockBOP";
  const std::string BOPArrayProviderId = "MockBOPArray";
  const std::string PWMCProviderId = "MockPWMC";
  
  class MockHardwareManager : public HardwareManager {
  public:
    
    MockHardwareManager();

    std::shared_ptr<MockHardwareProvider<BinaryInputPin, MockBIP>> bipProvider;
    std::shared_ptr<MockHardwareProvider<BinaryOutputPin, MockBOP>> bopProvider;
    std::shared_ptr<MockBOPArrayProvider> bopArrayProvider;
    std::shared_ptr<MockHardwareProvider<PWMChannel, MockPWMChannel>> pwmChannelProvider;
  };
}
