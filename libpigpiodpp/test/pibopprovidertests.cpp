#include <boost/test/unit_test.hpp>

#include "pigpiodpp/pimanager.hpp"
#include "pigpiodpp/gpiopin.hpp"
#include "pigpiodpp/pibopprovider.hpp"
#include "pigpiodpp/pinassignedexception.hpp"

BOOST_AUTO_TEST_SUITE( PiBOPProvider )

BOOST_AUTO_TEST_CASE( Smoke )
{
  auto pm = PiGPIOdpp::PiManager::CreatePiManager();

  PiGPIOdpp::PiBOPProvider pbp(pm);

  std::string deviceId = "10";
  Tendril::SettingsMap settings;

  auto res = pbp.GetHardware(deviceId, settings);
  BOOST_REQUIRE( res );

  auto gpio = dynamic_cast<PiGPIOdpp::GPIOPin*>(res.get());
  BOOST_REQUIRE( gpio );
}

BOOST_AUTO_TEST_CASE( NoDuplicates )
{
  auto pm = PiGPIOdpp::PiManager::CreatePiManager();

  PiGPIOdpp::PiBOPProvider pbp(pm);

  std::string deviceId = "10";
  Tendril::SettingsMap settings;

  auto res = pbp.GetHardware(deviceId, settings);
  BOOST_REQUIRE( res );

  BOOST_CHECK_EXCEPTION( pbp.GetHardware(deviceId, settings),
			 PiGPIOdpp::PinAssignedException,
			 [=](const PiGPIOdpp::PinAssignedException& pae) {
			   return pae.pinId == 10;
			 });
}

BOOST_AUTO_TEST_SUITE_END()
