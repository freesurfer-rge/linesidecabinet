#pragma once

#include "hardwaremanager.hpp"

#include "mockbipprovider.hpp"
#include "mockbopprovider.hpp"
#include "mockpwmchannelprovider.hpp"

class MockHardwareManager : public Lineside::HardwareManager {
public:
  const std::string BIPProviderId = "BIP";
  const std::string BOPProviderId = "BOP";
  const std::string PWMChannelProviderId = "PWM";
  
  MockHardwareManager();

  std::shared_ptr<MockBIPProvider> bipProvider;
  std::shared_ptr<MockBOPProvider> bopProvider;
  std::shared_ptr<MockPWMChannelProvider> pwmChannelProvider;
};
