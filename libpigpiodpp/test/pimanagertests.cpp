#include <boost/test/unit_test.hpp>

#include "pigpiodpp/pimanager.hpp"
#include "pigpiodpp/gpiopin.hpp"
#include "pigpiodpp/i2cpi.hpp"
#include "pigpiodpp/libraryexception.hpp"
#include "pigpiodpp/pinassignedexception.hpp"
#include "pigpiodpp/i2cdeviceassignedexception.hpp"

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
  gpio1->Set(false);
  // Even if we're using the stub, it will always return 0
  BOOST_CHECK( !gpio1->Get() );
  gpio1->Set(true);
#ifdef PIGPIODPP_HAVE_PIGPIO
  // Following can only work if we have a real Pi
  BOOST_CHECK( gpio1->Get() );
#endif
}

BOOST_AUTO_TEST_CASE( SmokeI2CPi )
{
  auto pm = PiGPIOdpp::PiManager::CreatePiManager();
  BOOST_CHECK_EQUAL( pm.use_count(), 1 );

  const unsigned int busId = 1;
  const unsigned int deviceId = 0x8;

  auto device = pm->GetI2CPi(busId, deviceId);
  BOOST_CHECK_EQUAL( device->getPi(), pm->getId() );
  BOOST_CHECK_EQUAL( device->getI2CBus(), busId );
  BOOST_CHECK_EQUAL( device->getI2CAddress(), deviceId );
  BOOST_CHECK( device->getHandle() >= 0 );
}

BOOST_AUTO_TEST_CASE( GetTwoI2CPi )
{
  auto pm = PiGPIOdpp::PiManager::CreatePiManager();
  BOOST_CHECK_EQUAL( pm.use_count(), 1 );

  const unsigned int busId = 1;
  auto dev0 = pm->GetI2CPi(busId, 0);
  BOOST_REQUIRE( dev0 );
  BOOST_CHECK_NO_THROW( pm->GetI2CPi(busId, 1) );
}

BOOST_AUTO_TEST_CASE( PinOutOfRange )
{
  auto pm = PiGPIOdpp::PiManager::CreatePiManager();
  BOOST_CHECK_EQUAL( pm.use_count(), 1 );
  
  BOOST_CHECK_THROW( pm->GetGPIOPin(1024),
		     std::out_of_range );
}

BOOST_AUTO_TEST_CASE( DuplicatePin )
{
  auto pm = PiGPIOdpp::PiManager::CreatePiManager();
  BOOST_CHECK_EQUAL( pm.use_count(), 1 );

  auto pin0 = pm->GetGPIOPin(2);

  BOOST_CHECK_EXCEPTION( pm->GetI2CPi(1, 10),
			 PiGPIOdpp::PinAssignedException,
			 [=](const PiGPIOdpp::PinAssignedException& pae) {
			   return pae.pinId == 2;
			 });
}

BOOST_AUTO_TEST_CASE( DuplicateI2CDevice )
{
  auto pm = PiGPIOdpp::PiManager::CreatePiManager();
  BOOST_CHECK_EQUAL( pm.use_count(), 1 );

  const unsigned int busId = 1;
  const unsigned int deviceId = 0x1;

  auto dev0 = pm->GetI2CPi(busId, deviceId);

  BOOST_CHECK_EXCEPTION( pm->GetI2CPi(busId, deviceId),
			 PiGPIOdpp::I2CDeviceAssignedException,
			 [=](const PiGPIOdpp::I2CDeviceAssignedException& i2cdae) {
			   bool result = (i2cdae.busId == busId);
			   result = result && ( i2cdae.deviceId == deviceId);
			   return result;
			 });
}

BOOST_AUTO_TEST_SUITE_END()
