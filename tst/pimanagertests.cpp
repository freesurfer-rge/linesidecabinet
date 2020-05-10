#include <boost/test/unit_test.hpp>

#include "exceptionmessagecheck.hpp"

#include "pigpiod/pimanager.hpp"
#include "pigpiod/gpiopin.hpp"
#include "pigpiod/pigpiodexceptions.hpp"

BOOST_AUTO_TEST_SUITE( PiManager )

BOOST_AUTO_TEST_CASE( Smoke )
{
  auto pm = Lineside::PiGPIOd::PiManager::CreatePiManager();
  BOOST_CHECK_EQUAL( pm.use_count(), 1 );
}

BOOST_AUTO_TEST_CASE( NoDoubleInitialise )
{
  auto pm = Lineside::PiGPIOd::PiManager::CreatePiManager();
  BOOST_CHECK_EQUAL( pm.use_count(), 1 );

  std::string msg("CreatePiManager: Already initialised");
  BOOST_CHECK_EXCEPTION( Lineside::PiGPIOd::PiManager::CreatePiManager(),
			 std::logic_error,
			 GetExceptionMessageChecker<std::logic_error>(msg) );
}

BOOST_AUTO_TEST_CASE( SmokeGetGPIOPin )
{
  auto pm = Lineside::PiGPIOd::PiManager::CreatePiManager();
  BOOST_CHECK_EQUAL( pm.use_count(), 1 );

  auto gpio1 = pm->GetGPIOPin(1);
  BOOST_REQUIRE( gpio1 );
  BOOST_CHECK_EQUAL( pm.use_count(), 2 );

  gpio1->SetMode( Lineside::PiGPIOd::GPIOMode::Output );
}

#ifdef HAVE_PIGPIO
/*
  The following look for responses from the real PiGPIOd library
  As such, they have to run on a Pi
 */
BOOST_AUTO_TEST_CASE( SmokeGPIOPinException )
{
  auto pm = Lineside::PiGPIOd::PiManager::CreatePiManager();
  BOOST_CHECK_EQUAL( pm.use_count(), 1 );

  /*
    The value requested is too big, but this isn't checked until
    pigpiod
  */
  auto gpio1 = pm->GetGPIOPin(1024);
  BOOST_REQUIRE( gpio1 );

  std::string msg("Error from pigpiod on calling 'set_mode'. Error code is '-3' with explanation: GPIO not 0-53");
  BOOST_CHECK_EXCEPTION( gpio1->SetMode( Lineside::PiGPIOd::GPIOMode::Output ),
			 Lineside::PiGPIOd::PiGPIOdException,
			 GetExceptionMessageChecker<Lineside::PiGPIOd::PiGPIOdException>(msg) );
}

#endif

BOOST_AUTO_TEST_SUITE_END()