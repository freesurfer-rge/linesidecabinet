#include <boost/test/unit_test.hpp>

#include "tendril/mocks/mockhardwaremanager.hpp"

BOOST_AUTO_TEST_SUITE(MockHardwareManager)

BOOST_AUTO_TEST_CASE( Smoke )
{
  Tendril::Mocks::MockHardwareManager hw;

  BOOST_REQUIRE( hw.bopProviderRegistrar.Retrieve( hw.BOPProviderId ) );
  BOOST_REQUIRE( hw.bipProviderRegistrar.Retrieve( hw.BIPProviderId ) );
  BOOST_REQUIRE( hw.bopArrayProviderRegistrar.Retrieve( hw.BOPArrayProviderId ) );
  BOOST_REQUIRE( hw.pwmcProviderRegistrar.Retrieve( hw.PWMCProviderId ) );
}

BOOST_AUTO_TEST_SUITE_END()
