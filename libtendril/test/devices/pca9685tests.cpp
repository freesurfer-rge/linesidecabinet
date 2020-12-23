#include <boost/test/unit_test.hpp>

#include "tendril/mocks/mocki2ccommunicator.hpp"

#include "tendril/devices/pca9685.hpp"
#include "tendril/devices/pca9685channel.hpp"

BOOST_AUTO_TEST_SUITE(Devices)

BOOST_AUTO_TEST_SUITE(PCA9685)

BOOST_AUTO_TEST_CASE(Smoke)
{
  auto comms = std::unique_ptr<Tendril::I2CCommunicator>(new Tendril::Mocks::MockI2CCommunicator());
  BOOST_REQUIRE( comms );

  const std::string devName = "Test";
  Tendril::SettingsMap devSettings;
  devSettings["referenceClock"] = "25e6";
  devSettings["pwmFrequency"] = "60";
  auto pca9685 = std::make_shared<Tendril::Devices::PCA9685>(devName,
							     devSettings,
							     comms);
  BOOST_REQUIRE( pca9685 );
  BOOST_CHECK( !comms );
  BOOST_CHECK_EQUAL( pca9685->name, devName );

  // Now try getting a channel
  const std::string channelId = "00";
  Tendril::SettingsMap channelSettings;

  auto pwmc = pca9685->GetHardware(channelId, channelSettings);
  BOOST_REQUIRE( pwmc );
  auto pca9685channel = dynamic_cast<Tendril::Devices::PCA9685Channel*>(pwmc.get());
  BOOST_CHECK( pca9685channel );
  
  BOOST_CHECK_NO_THROW( pwmc->Set(0,128) );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
