#include <stdexcept>

#include "mockhardwaremanager.hpp"

Lineside::BOPProviderRegistrar* MockHardwareManager::GetBOPProviderRegistrar() {
  throw std::logic_error("Not yet implemented");
}

Lineside::BIPProviderRegistrar* MockHardwareManager::GetBIPProviderRegistrar() {
  throw std::logic_error("Not yet implemented");
}

Lineside::PWMCProviderRegistrar* MockHardwareManager::GetPWMCProviderRegistrar() {
  throw std::logic_error("Not yet implemented");
}
