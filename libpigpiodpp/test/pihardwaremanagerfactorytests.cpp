#include <boost/test/unit_test.hpp>

#include "tendril/devices/i2cdevicedata.hpp"
#include "tendril/devices/pca9685.hpp"

#include "pigpiodpp/pihardwaremanagerfactory.hpp"

BOOST_AUTO_TEST_SUITE( PiHardwareManagerFactory )

BOOST_AUTO_TEST_CASE( Smoke )
{
  Tendril::HardwareManagerData config;
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
  
  auto some9685 = std::make_shared<
    Tendril::Devices::I2CDeviceData<Tendril::Devices::PCA9685>>();
  some9685->i2cCommsRequest.providerName = "1";
  some9685->i2cCommsRequest.idOnProvider = "0x10";
  some9685->name = devName;
  some9685->settings["referenceClock"] = "25e6";
  some9685->settings["pwmFrequency"] = "60";
  
  Tendril::HardwareManagerData config;
  config.devices.push_back(some9685);
  
  auto hwm = PiGPIOdpp::GetHardwareManager(config);
  BOOST_REQUIRE( hwm );

  BOOST_CHECK( hwm->bipProviderRegistrar.Retrieve("GPIO") );
  BOOST_CHECK( hwm->bopProviderRegistrar.Retrieve("GPIO") );
  BOOST_CHECK( hwm->bopArrayProviderRegistrar.Retrieve("GPIO") );
  BOOST_CHECK( hwm->pwmcProviderRegistrar.Retrieve( devName ) );
}

BOOST_AUTO_TEST_SUITE_END()
