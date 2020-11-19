#include <boost/test/unit_test.hpp>

#include "pigpiodpp/pimanager.hpp"
#include "pigpiodpp/gpiopin.hpp"
#include "pigpiodpp/pibipprovider.hpp"
#include "pigpiodpp/pinassignedexception.hpp"

BOOST_AUTO_TEST_SUITE( PiBIPProvider )

BOOST_AUTO_TEST_CASE( Smoke )
{
  auto pm = PiGPIOdpp::PiManager::CreatePiManager();

  PiGPIOdpp::PiBIPProvider pbp(pm);

  std::string deviceId = "11";
  Tendril::SettingsMap settings;
  settings["pud"] = "Down";
  settings["glitch"] = "100000";

  auto res = pbp.GetHardware(deviceId, settings);
  BOOST_REQUIRE( res );

  auto gpiopin = dynamic_cast<PiGPIOdpp::GPIOPin*>(res.get());
  BOOST_REQUIRE( gpiopin );
}

BOOST_AUTO_TEST_SUITE_END()
