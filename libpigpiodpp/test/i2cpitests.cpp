#include <boost/test/unit_test.hpp>

#include "pigpiodpp/libraryexception.hpp"
#include "pigpiodpp/i2cpi.hpp"

#ifdef PIGPIODPP_HAVE_PIGPIO
const bool haveHardware = true;
#else
const bool haveHardware = false;
#endif

BOOST_AUTO_TEST_SUITE( I2CPi )

BOOST_AUTO_TEST_CASE( Smoke )
{
  auto pm = PiGPIOdpp::PiManager::CreatePiManager();

  const unsigned int busId = 0;
  const unsigned int deviceId = 0x1;

  if( haveHardware ) {
    // Expect failure (on a bare Pi)
    BOOST_CHECK_THROW(PiGPIOdpp::I2CPi i2cDev(pm, busId, deviceId),
		      PiGPIOdpp::LibraryException);
  } else {
    PiGPIOdpp::I2CPi i2cDev(pm, busId, deviceId);
    
    BOOST_CHECK_EQUAL( i2cDev.getPi(), pm->getId() );
    BOOST_CHECK_EQUAL( i2cDev.getI2CBus(), busId );
    BOOST_CHECK_EQUAL( i2cDev.getI2CAddress(), deviceId );
    BOOST_CHECK( i2cDev.getHandle() >= 0 );
  }
}
  
BOOST_AUTO_TEST_CASE( WriteByte )
{
  auto pm = PiGPIOdpp::PiManager::CreatePiManager();

  const unsigned int busId = 0;
  const unsigned int deviceId = 0x1;

  if( haveHardware ) {
    // Expect failure (on a bare Pi)
    BOOST_CHECK_THROW(PiGPIOdpp::I2CPi i2cDev(pm, busId, deviceId),
		      PiGPIOdpp::LibraryException);
  } else {
    PiGPIOdpp::I2CPi i2cDev(pm, busId, deviceId);
  
    BOOST_CHECK_NO_THROW( i2cDev.WriteByte(1, 2) );
  }
}

BOOST_AUTO_TEST_CASE( WriteWord )
{
  auto pm = PiGPIOdpp::PiManager::CreatePiManager();

  const unsigned int busId = 0;
  const unsigned int deviceId = 0x1;

  if( haveHardware ) {
    // Expect failure (on a bare Pi)
    BOOST_CHECK_THROW(PiGPIOdpp::I2CPi i2cDev(pm, busId, deviceId),
		      PiGPIOdpp::LibraryException);
  } else {
    PiGPIOdpp::I2CPi i2cDev(pm, busId, deviceId);

    BOOST_CHECK_NO_THROW( i2cDev.WriteWord(4, 5) );
  }
}

BOOST_AUTO_TEST_SUITE_END()
