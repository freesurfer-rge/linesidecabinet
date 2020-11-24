#include <boost/test/unit_test.hpp>

#include "tendril/mocks/utilities.hpp"

BOOST_AUTO_TEST_SUITE(Utilities)

BOOST_AUTO_TEST_CASE( SmokeMockHardwareManager )
{
  auto manager = Tendril::Mocks::GetMockHardwareManager();
  BOOST_REQUIRE(manager);

  BOOST_CHECK( manager->bopProviderRegistrar.Retrieve( Tendril::Mocks::BOPProviderId ) );
  BOOST_CHECK( manager->bipProviderRegistrar.Retrieve( Tendril::Mocks::BIPProviderId ) );
  BOOST_CHECK( manager->bopArrayProviderRegistrar.Retrieve( Tendril::Mocks::BOPArrayProviderId ) );
  BOOST_CHECK( manager->pwmcProviderRegistrar.Retrieve( Tendril::Mocks::PWMCProviderId ) );
}

BOOST_AUTO_TEST_SUITE_END()
