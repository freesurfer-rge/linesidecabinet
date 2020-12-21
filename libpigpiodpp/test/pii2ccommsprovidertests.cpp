#include <boost/test/unit_test.hpp>

#include "pigpiodpp/pimanager.hpp"
#include "pigpiodpp/i2cpi.hpp"
#include "pigpiodpp/i2cdeviceassignedexception.hpp"
#include "pigpiodpp/pii2ccommsprovider.hpp"

BOOST_AUTO_TEST_SUITE( PiI2CCommsProvider )

BOOST_AUTO_TEST_CASE( Smoke )
{
  auto pm = PiGPIOdpp::PiManager::CreatePiManager();

  const unsigned int myBus = 1;
  PiGPIOdpp::PiI2CCommsProvider i2ccp(pm, myBus);

  BOOST_CHECK_EQUAL( i2ccp.getPi(), pm->getId() );
  BOOST_CHECK_EQUAL( i2ccp.getBusId(), myBus);

  std::string deviceId = "11";
  Tendril::SettingsMap settings;

  auto res = i2ccp.GetHardware(deviceId, settings);
  BOOST_REQUIRE( res );

  auto i2cpi = dynamic_cast<PiGPIOdpp::I2CPi*>(res.get());
  BOOST_REQUIRE( i2cpi );
  BOOST_CHECK_EQUAL( i2cpi->getPi(), pm->getId() );
  BOOST_CHECK_EQUAL( i2cpi->getI2CBus(), myBus );
  BOOST_CHECK_EQUAL( i2cpi->getI2CAddress(), 11 );
}

BOOST_AUTO_TEST_CASE( NoDuplicates )
{
  auto pm = PiGPIOdpp::PiManager::CreatePiManager();

  const unsigned int myBus = 1;
  PiGPIOdpp::PiI2CCommsProvider i2ccp(pm, myBus);

  BOOST_CHECK_EQUAL( i2ccp.getPi(), pm->getId() );
  BOOST_CHECK_EQUAL( i2ccp.getBusId(), myBus);

  std::string deviceId = "11";
  Tendril::SettingsMap settings;

  auto res = i2ccp.GetHardware(deviceId, settings);
  BOOST_REQUIRE( res );

  BOOST_CHECK_EXCEPTION( i2ccp.GetHardware(deviceId, settings),
			 PiGPIOdpp::I2CDeviceAssignedException,
			 [=](const PiGPIOdpp::I2CDeviceAssignedException& iae) {
			   BOOST_CHECK_EQUAL( iae.busId, myBus );
			   BOOST_CHECK_EQUAL( iae.deviceId, 11 );
			   return (iae.deviceId == 11) && (iae.busId == myBus);
			 });
}

BOOST_AUTO_TEST_SUITE_END()
