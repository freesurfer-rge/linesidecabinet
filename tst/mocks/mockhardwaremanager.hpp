#pragma once

#include "hardwaremanager.hpp"

class MockHardwareManager : Lineside::HardwareManager {
public:
  virtual Lineside::BOPProviderRegistrar* GetBOPProviderRegistrar() override;
  virtual Lineside::BIPProviderRegistrar* GetBIPProviderRegistrar() override;
  virtual Lineside::PWMCProviderRegistrar* GetPWMCProviderRegistrar() override;
};
