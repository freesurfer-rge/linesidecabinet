#include <boost/test/unit_test.hpp>

#include "pigpiodpp/pihardwaremanagerfactory.hpp"

BOOST_AUTO_TEST_SUITE( PiHardwareManagerFactory )

BOOST_AUTO_TEST_CASE( Smoke )
{
  std::vector<Tendril::Devices::I2CDeviceData> devices;
  Tendril::HardwareManagerData config;
  config.i2cDevices = devices;
  auto hwm = PiGPIOdpp::GetHardwareManager(config);
  BOOST_REQUIRE( hwm );

  BOOST_CHECK( hwm->bipProviderRegistrar.Retrieve("GPIO") );
  BOOST_CHECK( hwm->bopProviderRegistrar.Retrieve("GPIO") );
  BOOST_CHECK( hwm->bopArrayProviderRegistrar.Retrieve("GPIO") );
  BOOST_CHECK( hwm->i2cCommProviderRegistrar.Retrieve("0") );
  BOOST_CHECK( hwm->i2cCommProviderRegistrar.Retrieve("1") );
}

BOOST_AUTO_TEST_CASE( WithPCA9685 )
{
  const std::string devName = "MyServoProvider";
  Tendril::Devices::I2CDeviceData some9685;
  some9685.kind = "pca9685";
  some9685.bus = 1;
  some9685.address = 0x10;
  some9685.name = devName;
  some9685.settings["referenceClock"] = "25e6";
  some9685.settings["pwmFrequency"] = "60";
  std::vector<Tendril::Devices::I2CDeviceData> devices;
  devices.push_back(some9685);
  Tendril::HardwareManagerData config;
  config.i2cDevices = devices;
  
  auto hwm = PiGPIOdpp::GetHardwareManager(config);
  BOOST_REQUIRE( hwm );

  BOOST_CHECK( hwm->bipProviderRegistrar.Retrieve("GPIO") );
  BOOST_CHECK( hwm->bopProviderRegistrar.Retrieve("GPIO") );
  BOOST_CHECK( hwm->bopArrayProviderRegistrar.Retrieve("GPIO") );
  BOOST_CHECK( hwm->pwmcProviderRegistrar.Retrieve( devName ) );
}

BOOST_AUTO_TEST_SUITE_END()
