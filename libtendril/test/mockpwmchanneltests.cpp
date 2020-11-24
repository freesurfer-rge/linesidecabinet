#include <boost/test/unit_test.hpp>

#include "tendril/mocks/mockpwmchannel.hpp"

BOOST_AUTO_TEST_SUITE(MockPWMChannel)

BOOST_AUTO_TEST_CASE( Set )
{
  Tendril::Mocks::MockPWMChannel mpwmc;
  BOOST_CHECK_EQUAL( mpwmc.updates.size(), 0 );

  mpwmc.Set( 10, 20 );
  BOOST_CHECK_EQUAL( mpwmc.updates.size(), 1 );
  auto lastUpdate = mpwmc.updates.at(0);
  BOOST_CHECK_EQUAL( lastUpdate.first, 10 );
  BOOST_CHECK_EQUAL( lastUpdate.second, 20 );

  mpwmc.Set( 14, 16 );
  BOOST_CHECK_EQUAL( mpwmc.updates.size(), 2 );
  lastUpdate = mpwmc.updates.at(1);
  BOOST_CHECK_EQUAL( lastUpdate.first, 14 );
  BOOST_CHECK_EQUAL( lastUpdate.second, 16 );  
}

BOOST_AUTO_TEST_SUITE_END()
