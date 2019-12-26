#pragma once

#include "hardwaremanager.hpp"

#include "mockbopprovider.hpp"
#include "mockpwmchannelprovider.hpp"

class MockHardwareManager : public Lineside::HardwareManager {
public:
  const std::string BOPProviderId = "BOP";
  const std::string PWMChannelProviderId = "PWM";
  
  MockHardwareManager() :
    HardwareManager(),
    bopProvider(std::make_shared<MockBOPProvider>()),
    pwmChannelProvider(std::make_shared<MockPWMChannelProvider>()),
    bopProviderRegistrar(std::make_shared<Lineside::BOPProviderRegistrar>()),
    pwmChannelProviderRegistrar(std::make_shared<Lineside::PWMCProviderRegistrar>()) {
    this->bopProviderRegistrar->Register( BOPProviderId, this->bopProvider );
    this->pwmChannelProviderRegistrar->Register( PWMChannelProviderId, this->pwmChannelProvider );
  }

  std::shared_ptr<MockBOPProvider> bopProvider;
  std::shared_ptr<MockPWMChannelProvider> pwmChannelProvider;

  std::shared_ptr<Lineside::BOPProviderRegistrar> bopProviderRegistrar;
  std::shared_ptr<Lineside::PWMCProviderRegistrar> pwmChannelProviderRegistrar;
  
  virtual std::weak_ptr<Lineside::BOPProviderRegistrar> GetBOPProviderRegistrar() override;
  virtual std::weak_ptr<Lineside::BIPProviderRegistrar> GetBIPProviderRegistrar() override;
  virtual std::weak_ptr<Lineside::PWMCProviderRegistrar> GetPWMCProviderRegistrar() override;
};
