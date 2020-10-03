#include <boost/test/unit_test.hpp>

#include "lineside/pi/pca9685.hpp"
#include "lineside/pi/i2cdevicefactory.hpp"

BOOST_AUTO_TEST_SUITE( pi )

BOOST_AUTO_TEST_SUITE( PCA9685 )

BOOST_AUTO_TEST_CASE( Smoke )
{
  const std::string devName = "Test";
  std::map<std::string,std::string> settings;
  
  auto pm = PiGPIOdpp::PiManager::CreatePiManager();

  std::shared_ptr<Lineside::Pi::I2CDevice> device;
  {
    Lineside::I2CDeviceData data;
    data.kind = "PCA9685";
    data.bus = 0;
    data.address = 1;
    data.name = devName;
    data.settings = settings;

    Lineside::Pi::I2CDeviceFactory f;

    device = f.Manufacture(*pm, data);
  }
  BOOST_CHECK( device );

  BOOST_CHECK_EQUAL(pm.use_count(), 2);
}


BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
