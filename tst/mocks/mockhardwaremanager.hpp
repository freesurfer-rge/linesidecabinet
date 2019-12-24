#pragma once

#include "hardwaremanager.hpp"

#include "mockpwmchannelprovider.hpp"

class MockHardwareManager : public Lineside::HardwareManager {
public:
  const std::string PWMChannelProviderId = "PWM";
  
  MockHardwareManager() :
    HardwareManager(),
    pwmChannelProvider(std::make_shared<MockPWMChannelProvider>()),
    pwmChannelProviderRegistrar(std::make_shared<Lineside::PWMCProviderRegistrar>()) {
    this->pwmChannelProviderRegistrar->Register( PWMChannelProviderId, this->pwmChannelProvider );
  }
  
  std::shared_ptr<MockPWMChannelProvider> pwmChannelProvider;
  
  std::shared_ptr<Lineside::PWMCProviderRegistrar> pwmChannelProviderRegistrar;
  
  virtual std::weak_ptr<Lineside::BOPProviderRegistrar> GetBOPProviderRegistrar() override;
  virtual std::weak_ptr<Lineside::BIPProviderRegistrar> GetBIPProviderRegistrar() override;
  virtual std::weak_ptr<Lineside::PWMCProviderRegistrar> GetPWMCProviderRegistrar() override;
};
