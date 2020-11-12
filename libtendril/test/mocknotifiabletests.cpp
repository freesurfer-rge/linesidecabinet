#include <boost/test/unit_test.hpp>

#include "tendril/mocks/mocknotifiable.hpp"

BOOST_AUTO_TEST_SUITE( MockNotifiable )

BOOST_AUTO_TEST_CASE( Notify )
{
  Tendril::Mocks::MockNotifiable<bool> mn;

  mn.Notify(true);
  BOOST_CHECK_EQUAL( mn.lastNotification, true );
  mn.Notify(false);
  BOOST_CHECK_EQUAL( mn.lastNotification, false );
}

BOOST_AUTO_TEST_SUITE_END()
