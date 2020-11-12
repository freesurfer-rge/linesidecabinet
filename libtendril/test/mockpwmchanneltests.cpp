#include <boost/test/unit_test.hpp>

#include "tendril/mocks/mockpwmchannel.hpp"

BOOST_AUTO_TEST_SUITE(MockPWMChannel)

BOOST_AUTO_TEST_CASE( Set )
{
  Tendril::Mocks::MockPWMChannel mpwmc;

  BOOST_CHECK_EQUAL( mpwmc.lastStart, 0 );
  BOOST_CHECK_EQUAL( mpwmc.lastStop, 0 );

  mpwmc.Set(10, 20);
  BOOST_CHECK_EQUAL( mpwmc.lastStart, 10 );
  BOOST_CHECK_EQUAL( mpwmc.lastStop, 20 );
}

BOOST_AUTO_TEST_SUITE_END()
