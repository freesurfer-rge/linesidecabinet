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
  
  MockHardwareManager() :
    HardwareManager(),
    bipProvider(std::make_shared<MockBIPProvider>()),
    bopProvider(std::make_shared<MockBOPProvider>()),
    pwmChannelProvider(std::make_shared<MockPWMChannelProvider>()) {
    this->bipProviderRegistrar.Register( BIPProviderId, this->bipProvider );
    this->bopProviderRegistrar.Register( BOPProviderId, this->bopProvider );
    this->pwmcProviderRegistrar.Register( PWMChannelProviderId, this->pwmChannelProvider );
  }

  std::shared_ptr<MockBIPProvider> bipProvider;
  std::shared_ptr<MockBOPProvider> bopProvider;
  std::shared_ptr<MockPWMChannelProvider> pwmChannelProvider;
};
