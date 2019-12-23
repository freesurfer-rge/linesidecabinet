#pragma once

#include "hardwaremanager.hpp"

class MockHardwareManager : public Lineside::HardwareManager {
public:
  virtual std::weak_ptr<Lineside::BOPProviderRegistrar> GetBOPProviderRegistrar() override;
  virtual std::weak_ptr<Lineside::BIPProviderRegistrar> GetBIPProviderRegistrar() override;
  virtual std::weak_ptr<Lineside::PWMCProviderRegistrar> GetPWMCProviderRegistrar() override;
};
