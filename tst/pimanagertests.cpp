#include <boost/test/unit_test.hpp>

#include "exceptionmessagecheck.hpp"

#include "pigpiod/pimanager.hpp"
#include "pigpiod/gpiomanager.hpp"

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

BOOST_AUTO_TEST_CASE( SmokeGPIOManager )
{
  auto pm = Lineside::PiGPIOd::PiManager::CreatePiManager();
  BOOST_CHECK_EQUAL( pm.use_count(), 1 );

  auto gpioManager = pm->GetGPIOManager();
  BOOST_REQUIRE( gpioManager );
  BOOST_CHECK_EQUAL( pm.use_count(), 2 );

  gpioManager->SetMode( 12, Lineside::PiGPIOd::GPIOMode::Output );
}

#ifdef HAVE_PIGPIO
/*
  The following look for responses from the real PiGPIOd library
  As such, they have to run on a Pi
 */
BOOST_AUTO_TEST_CASE( SmokeGPIOManagerException )
{
  auto pm = Lineside::PiGPIOd::PiManager::CreatePiManager();
  BOOST_CHECK_EQUAL( pm.use_count(), 1 );

  auto gpioManager = pm->GetGPIOManager();
  BOOST_REQUIRE( gpioManager );

  std::string msg("Something");
  BOOST_CHECK_EXCEPTION( gpioManager->SetMode( 1024, Lineside::PiGPIOd::GPIOMode::Output ),
			 Lineside::PiGPIOd::PiGPIOdException,
			 GetExceptionMessageChecker<Lineside::PiGPIOd::PiGPIOdException>(msg) );
}

#endif

BOOST_AUTO_TEST_SUITE_END()
