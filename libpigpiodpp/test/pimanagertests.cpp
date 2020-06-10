#include <boost/test/unit_test.hpp>

#include "pigpiodpp/pimanager.hpp"
#include "pigpiodpp/gpiopin.hpp"
#include "pigpiodpp/i2cdevice.hpp"
#include "pigpiodpp/pigpiodppexception.hpp"

#ifdef PIGPIODPP_HAVE_PIGPIO
const bool haveHardware = true;
#else
const bool haveHardware = false;
#endif

BOOST_AUTO_TEST_SUITE( PiManager )

BOOST_AUTO_TEST_CASE( Smoke )
{
  auto pm = PiGPIOdpp::PiManager::CreatePiManager();
  BOOST_CHECK_EQUAL( pm.use_count(), 1 );
}

BOOST_AUTO_TEST_CASE( NoDoubleInitialise )
{
  auto pm = PiGPIOdpp::PiManager::CreatePiManager();
  BOOST_CHECK_EQUAL( pm.use_count(), 1 );

  std::string msg("CreatePiManager: Already initialised");
  BOOST_CHECK_THROW( PiGPIOdpp::PiManager::CreatePiManager(),
		     std::logic_error );
}

BOOST_AUTO_TEST_CASE( SmokeGPIOPinOutput )
{
  auto pm = PiGPIOdpp::PiManager::CreatePiManager();
  BOOST_CHECK_EQUAL( pm.use_count(), 1 );

  // Have to pick a 'safe' GPIO for real hardware
  auto gpio1 = pm->GetGPIOPin(5);
  BOOST_REQUIRE( gpio1 );
  BOOST_CHECK_EQUAL( pm.use_count(), 2 );
  
  gpio1->SetMode( PiGPIOdpp::GPIOMode::Output );
  gpio1->Write(false);
  // Even if we're using the stub, it will always return 0
  BOOST_CHECK( !gpio1->Read() );
  gpio1->Write(true);
#ifdef PIGPIODPP_HAVE_PIGPIO
  // Following can only work if we have a real Pi
  BOOST_CHECK( gpio1->Read() );
#endif
}

BOOST_AUTO_TEST_CASE( SmokeI2CDevice )
{
  auto pm = PiGPIOdpp::PiManager::CreatePiManager();
  BOOST_CHECK_EQUAL( pm.use_count(), 1 );

  if( haveHardware ) {
    // Expect failure since nothing is connected (probably)
    BOOST_FAIL("Need to fill in");
  } else {
    const unsigned int busId = 0;
    const unsigned int deviceId = 0x1;
    auto device = pm->GetI2CDevice(busId, deviceId);
    BOOST_CHECK_EQUAL( device->getPi(), pm->getId() );
    BOOST_CHECK_EQUAL( device->getI2CBus(), busId );
    BOOST_CHECK_EQUAL( device->getI2CAddress(), deviceId );
    BOOST_CHECK( device->getHandle() >= 0 );
  }
}

#ifdef PIGPIODPP_HAVE_PIGPIO
/*
  The following look for responses from the real PiGPIOd library
  As such, they have to run on a Pi
 */
BOOST_AUTO_TEST_CASE( SmokeGPIOPinException )
{
  auto pm = PiGPIOdpp::PiManager::CreatePiManager();
  BOOST_CHECK_EQUAL( pm.use_count(), 1 );

  /*
    The value requested is too big, but this isn't checked until
    pigpiod
  */
  auto gpio1 = pm->GetGPIOPin(1024);
  BOOST_REQUIRE( gpio1 );

  BOOST_CHECK_THROW( gpio1->SetMode( PiGPIOdpp::GPIOMode::Output ),
		     PiGPIOdpp::PiGPIOdppException );
}


#endif

BOOST_AUTO_TEST_SUITE_END()
