#include <boost/test/unit_test.hpp>

#include "pigpiodpp/i2cdevice.hpp"

BOOST_AUTO_TEST_SUITE( I2CDevice )

BOOST_AUTO_TEST_CASE( Smoke )
{
  auto pm = PiGPIOdpp::PiManager::CreatePiManager();

  const unsigned int busId = 0;
  const unsigned int deviceId = 0x1;

  PiGPIOdpp::I2CDevice i2cDev(pm, busId, deviceId);

  BOOST_CHECK_EQUAL( i2cDev.getPi(), pm->getId() );
  BOOST_CHECK_EQUAL( i2cDev.getI2CBus(), busId );
  BOOST_CHECK_EQUAL( i2cDev.getI2CAddress(), deviceId );
  BOOST_CHECK( i2cDev.getHandle() >= 0 );
}

BOOST_AUTO_TEST_SUITE_END()
