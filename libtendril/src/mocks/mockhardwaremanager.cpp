#include "tendril/mocks/mockhardwaremanager.hpp"

namespace Tendril::Mocks {
  MockHardwareManager::MockHardwareManager()
    : HardwareManager(),
      bipProvider(std::make_shared<MockHardwareProvider<BinaryInputPin, MockBIP>>()),
      bopProvider(std::make_shared<MockHardwareProvider<BinaryOutputPin, MockBOP>>()),
      bopArrayProvider(std::make_shared<MockBOPArrayProvider>()),
      pwmChannelProvider(std::make_shared<MockHardwareProvider<PWMChannel, MockPWMChannel>>()) {
    this->bipProviderRegistrar.Register( BIPProviderId, this->bipProvider );
    this->bopProviderRegistrar.Register( BOPProviderId, this->bopProvider );
    this->bopArrayProviderRegistrar.Register( BOPArrayProviderId, this->bopArrayProvider );
    this->pwmcProviderRegistrar.Register( PWMCProviderId, this->pwmChannelProvider );
  }
}
