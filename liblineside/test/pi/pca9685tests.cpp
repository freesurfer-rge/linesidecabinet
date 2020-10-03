#include <boost/test/unit_test.hpp>

#include "pigpiodpp/piavailable.hpp"

#include "lineside/pi/pca9685.hpp"
#include "lineside/pi/pca9685channel.hpp"
#include "lineside/pi/i2cdevicefactory.hpp"

BOOST_AUTO_TEST_SUITE( pi )

BOOST_AUTO_TEST_SUITE( PCA9685,
		       * boost::unit_test::enable_if<!PiGPIOdpp::piAvailable>() )

BOOST_AUTO_TEST_CASE( Smoke )
{
  const std::string devName = "Test";
  auto pm = PiGPIOdpp::PiManager::CreatePiManager();

  std::shared_ptr<Lineside::Pi::I2CDevice> device;
  {
    Lineside::I2CDeviceData data;
    data.kind = "pca9685";
    data.bus = 0;
    data.address = 1;
    data.name = devName;
    data.settings["referenceClock"] = "25e6";
    data.settings["pwmFrequency"] = "50";

    Lineside::Pi::I2CDeviceFactory f;

    device = f.Manufacture(*pm, data);
    BOOST_TEST_MESSAGE( "Device manufacture complete" );
  }
  BOOST_CHECK( device );
  BOOST_CHECK_EQUAL( device->name, devName );

  BOOST_CHECK_EQUAL(pm.use_count(), 2);
}

BOOST_AUTO_TEST_CASE( GetPCA9685Channel )
{
  std::unique_ptr<Lineside::PWMChannel> pwmChannel;

  // Nest so that all the explicit shared pointers are destructed
  {
    const std::string devName = "Test";
    auto pm = PiGPIOdpp::PiManager::CreatePiManager();
    
    std::shared_ptr<Lineside::Pi::I2CDevice> device;
    {
      Lineside::I2CDeviceData data;
      data.kind = "pca9685";
      data.bus = 0;
      data.address = 1;
      data.name = devName;
      data.settings["referenceClock"] = "25e6";
      data.settings["pwmFrequency"] = "50";
      
      Lineside::Pi::I2CDeviceFactory f;
      
      device = f.Manufacture(*pm, data);
      BOOST_TEST_MESSAGE( "Device manufacture complete" );
    }
    BOOST_REQUIRE( device );
    
    auto pca9685 = std::dynamic_pointer_cast<Lineside::Pi::PCA9685>(device);
    BOOST_REQUIRE( pca9685 );
    
    const std::string channelId = "10";
    std::map<std::string,std::string> channelSettings;

    pwmChannel = pca9685->GetHardware(channelId, channelSettings);
    BOOST_REQUIRE(pwmChannel);
    BOOST_TEST_MESSAGE( "Channel created" );
  }
  // If everything is set correctly internally, the following will still work
  pwmChannel->Set(10);
  BOOST_CHECK_EQUAL( pwmChannel->Get(), 10 );
  auto pca9685Channel = dynamic_cast<Lineside::Pi::PCA9685Channel*>(pwmChannel.get());
  BOOST_REQUIRE( pca9685Channel );
}


BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
