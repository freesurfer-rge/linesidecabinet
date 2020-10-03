#include <boost/test/unit_test.hpp>

#include "pigpiodpp/piavailable.hpp"
#include "lineside/pi/pihardwaremanager.hpp"
#include "lineside/pi/pca9685.hpp"

BOOST_AUTO_TEST_SUITE( pi )

BOOST_AUTO_TEST_SUITE( PiHardwareManager )

BOOST_AUTO_TEST_CASE( SmokeOutputPin )
{
  Lineside::HardwareManagerData hmd;

  Lineside::Pi::PiHardwareManager pi(hmd);

  auto bopProvider = pi.bopProviderRegistrar.Retrieve("GPIO");
  BOOST_REQUIRE( bopProvider );
  
  std::string pinId = "5";
  auto settings = std::map<std::string,std::string>();

  auto pin = bopProvider->GetHardware( pinId, settings );
  BOOST_REQUIRE(pin);
  // Should start with pin in off state
  BOOST_CHECK_EQUAL( pin->Get(), false );

  auto gpbop = dynamic_cast<Lineside::Pi::GPOutput*>(pin.get());
  BOOST_REQUIRE(gpbop);
}

BOOST_AUTO_TEST_CASE( SmokeInputPin )
{
  Lineside::HardwareManagerData hmd;
  Lineside::Pi::PiHardwareManager pi(hmd);

  auto bipProvider = pi.bipProviderRegistrar.Retrieve("GPIO");
  BOOST_REQUIRE( bipProvider );
  
  std::string pinId = "5";
  auto settings = std::map<std::string,std::string>();
  settings["pud"] = "Down";

  auto pin = bipProvider->GetHardware( pinId, settings );
  BOOST_REQUIRE(pin);
  // With the pulldown resistor, expect the pin to be off
  BOOST_CHECK_EQUAL( pin->Get(), false );

  auto gpbip = dynamic_cast<Lineside::Pi::GPInput*>(pin.get());
  BOOST_REQUIRE(gpbip);
}

BOOST_AUTO_TEST_CASE( CheckGPIODevice )
{
  Lineside::HardwareManagerData hmd;

  Lineside::Pi::PiHardwareManager pi(hmd);

  BOOST_CHECK_EQUAL( pi.GPIO, "GPIO" );
}

BOOST_AUTO_TEST_SUITE( I2C,
		       * boost::unit_test::enable_if<!PiGPIOdpp::piAvailable>() )

BOOST_AUTO_TEST_CASE( SmokePCA9685 )
{
  const std::string devName = "PCA1";
  
  Lineside::HardwareManagerData hmd;
  Lineside::I2CDeviceData pca9685Data;
  pca9685Data.kind = "pca9685";
  pca9685Data.bus = 0;
  pca9685Data.address = 1;
  pca9685Data.name = devName;
  pca9685Data.settings["referenceClock"] = "25e6";
  pca9685Data.settings["pwmFrequency"] = "50";
  hmd.i2cDevices.push_back(pca9685Data);

  Lineside::Pi::PiHardwareManager pi(hmd);

  auto pwmProvider = pi.pwmcProviderRegistrar.Retrieve(devName);
  BOOST_REQUIRE(pwmProvider);
  auto pca9685 = std::dynamic_pointer_cast<Lineside::Pi::PCA9685>(pwmProvider);
  BOOST_REQUIRE(pca9685);
  BOOST_CHECK_EQUAL( pca9685->name, devName );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
