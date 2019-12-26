#include <stdexcept>

#include "mockhardwaremanager.hpp"

std::weak_ptr<Lineside::BOPProviderRegistrar> MockHardwareManager::GetBOPProviderRegistrar() {
  return this->bopProviderRegistrar;
}

std::weak_ptr<Lineside::BIPProviderRegistrar> MockHardwareManager::GetBIPProviderRegistrar() {
  throw std::logic_error("Not yet implemented");
}

std::weak_ptr<Lineside::PWMCProviderRegistrar> MockHardwareManager::GetPWMCProviderRegistrar() {
  return this->pwmChannelProviderRegistrar;
}
