#include <boost/test/unit_test.hpp>

#include "tendril/mocks/utilities.hpp"
#include "tendril/mocks/mockhardwareprovider.hpp"

#include "tendril/devices/pca9685.hpp"
#include "tendril/devices/i2cdevicedata.hpp"

BOOST_AUTO_TEST_SUITE(Devices)

BOOST_AUTO_TEST_SUITE(I2CDeviceData)

BOOST_AUTO_TEST_CASE( SmokePCA9685 )
{
  auto hw = Tendril::Mocks::GetMockHardwareManager();

  const std::string devName = "MyPCA9685";
  Tendril::Devices::I2CDeviceData<Tendril::Devices::PCA9685> devData;
  devData.name = devName;
  devData.i2cCommsRequest.providerName = Tendril::Mocks::I2CProviderId; // The bus
  devData.i2cCommsRequest.idOnProvider = "0x20"; // The address
  // Following are specific to the PCA9685
  devData.settings["referenceClock"] = "25e6";
  devData.settings["pwmFrequency"] = "60";

  // Get the hardware registered
  devData.ConstructAndRegister(*hw);

  auto pwmcProvider = hw->pwmcProviderRegistrar.Retrieve(devName);
  BOOST_REQUIRE( pwmcProvider );
  auto pca9685 = std::dynamic_pointer_cast<Tendril::Devices::PCA9685>(pwmcProvider);
  BOOST_REQUIRE( pca9685 );
}

BOOST_AUTO_TEST_SUITE_END()
  
BOOST_AUTO_TEST_SUITE_END()
