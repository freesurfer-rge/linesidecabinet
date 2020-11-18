#include <boost/test/unit_test.hpp>

#include "tendril/mocks/mocknotifiable.hpp"
#include "pigpiodpp/gpiopin.hpp"

BOOST_AUTO_TEST_SUITE( GPIOPin )

BOOST_AUTO_TEST_CASE( Smoke )
{
  auto pm = PiGPIOdpp::PiManager::CreatePiManager();

  const int pinId = 5;
  PiGPIOdpp::GPIOPin pin(pm, pinId);
  
  BOOST_CHECK_EQUAL( pin.getPi(), pm->getId() );
  BOOST_CHECK_EQUAL( pin.getPin(), pinId );
}

#ifndef PIGPIODPP_HAVE_PIGPIO
BOOST_AUTO_TEST_CASE( CallBackInvoked )
{
  const unsigned char pinId = 5;
  auto pm = PiGPIOdpp::PiManager::CreatePiManager();

  PiGPIOdpp::GPIOPin pin(pm, pinId);

  auto mn = std::make_shared<Tendril::Mocks::MockNotifiable<bool>>();
  pin.RegisterListener(mn);

  // Check that notification happens
  mn->lastNotification = true;
  pin.TriggerNotifications(pin.getPi(), pinId, 0, 0);
  // May fail on a real Pi
  // The notification does its own read of the pin, and
  // in the stub library is hardwired to return false
  BOOST_CHECK_EQUAL( mn->lastNotification, false );
}
#endif

BOOST_AUTO_TEST_SUITE_END()
