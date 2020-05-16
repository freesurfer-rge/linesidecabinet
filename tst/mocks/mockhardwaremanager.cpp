#include <stdexcept>

#include "mockhardwaremanager.hpp"

MockHardwareManager::MockHardwareManager() :
  HardwareManager(),
  bipProvider(std::make_shared<MockBIPProvider>()),
  bopProvider(std::make_shared<MockBOPProvider>()),
  pwmChannelProvider(std::make_shared<MockPWMChannelProvider>()) {
  this->bipProviderRegistrar.Register( BIPProviderId, this->bipProvider );
  this->bopProviderRegistrar.Register( BOPProviderId, this->bopProvider );
  this->pwmcProviderRegistrar.Register( PWMChannelProviderId, this->pwmChannelProvider );
}
