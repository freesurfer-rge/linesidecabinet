#include <boost/test/unit_test.hpp>

#include "tendril/mocks/mocknotifiable.hpp"

#include "tendril/mocks/mockbip.hpp"

BOOST_AUTO_TEST_SUITE(MockBIP)

BOOST_AUTO_TEST_CASE( Get )
{
  Tendril::Mocks::MockBIP mb;

  BOOST_CHECK_EQUAL( mb.Get(), false );
  mb.state = true;
  BOOST_CHECK_EQUAL( mb.Get(), true );
  mb.state = false;
  BOOST_CHECK_EQUAL( mb.Get(), false );
}

BOOST_AUTO_TEST_CASE( Notify )
{
  auto target = std::make_shared<Tendril::Mocks::MockNotifiable<bool>>();

  Tendril::Mocks::MockBIP mb;

  mb.RegisterListener(target);

  mb.SendNotifications();
  BOOST_CHECK_EQUAL( target->lastNotification, false );

  mb.state = true;
  mb.SendNotifications();
  BOOST_CHECK_EQUAL( target->lastNotification, true );

  mb.state = false;
  mb.SendNotifications();
  BOOST_CHECK_EQUAL( target->lastNotification, false );
}

BOOST_AUTO_TEST_SUITE_END()
