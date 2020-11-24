#include "tendril/mocks/mockbop.hpp"
#include "tendril/mocks/mockbip.hpp"
#include "tendril/mocks/mockboparray.hpp"
#include "tendril/mocks/mockpwmchannel.hpp"

#include "tendril/mocks/mockbip.hpp"
#include "tendril/mocks/mockbop.hpp"
#include "tendril/mocks/mockpwmchannel.hpp"
#include "tendril/mocks/mockboparrayprovider.hpp"
#include "tendril/mocks/mockhardwareprovider.hpp"

#include "tendril/mocks/utilities.hpp"

namespace Tendril::Mocks {
  std::shared_ptr<HardwareManager> GetMockHardwareManager() {
    auto result = std::make_shared<HardwareManager>();

    auto bipProvider = std::make_shared<MockHardwareProvider<BinaryInputPin, MockBIP>>();
    result->bipProviderRegistrar.Register( BIPProviderId, bipProvider );

    auto bopProvider = std::make_shared<MockHardwareProvider<BinaryOutputPin, MockBOP>>();
    result->bopProviderRegistrar.Register( BOPProviderId, bopProvider );

    auto bopArrayProvider = std::make_shared<MockBOPArrayProvider>();
    result->bopArrayProviderRegistrar.Register( BOPArrayProviderId, bopArrayProvider );

    auto pwmChannelProvider = std::make_shared<MockHardwareProvider<PWMChannel, MockPWMChannel>>();
    result->pwmcProviderRegistrar.Register( PWMCProviderId, pwmChannelProvider );
    
    return result;
  }
}
