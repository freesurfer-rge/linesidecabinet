#pragma once

#include <memory>

#include "tendril/hardwaremanager.hpp"

namespace Tendril::Mocks {
  std::shared_ptr<HardwareManager> GetMockHardwareManager();
  
  const std::string BIPProviderId = "MockBIP";
  const std::string BOPProviderId = "MockBOP";
  const std::string BOPArrayProviderId = "MockBOPArray";
  const std::string PWMCProviderId = "MockPWMC";
}
