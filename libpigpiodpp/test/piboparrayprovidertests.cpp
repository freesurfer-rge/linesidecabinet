#include <boost/test/unit_test.hpp>

#include "pigpiodpp/pimanager.hpp"
#include "pigpiodpp/piboparray.hpp"
#include "pigpiodpp/piboparrayprovider.hpp"
#include "pigpiodpp/pinassignedexception.hpp"

BOOST_AUTO_TEST_SUITE( PiBOPArrayProvider )

BOOST_AUTO_TEST_CASE( Smoke )
{
  auto pm = PiGPIOdpp::PiManager::CreatePiManager();

  PiGPIOdpp::PiBOPArrayProvider pbap(pm);

  std::string deviceId = "ignored";
  Tendril::SettingsMap settings;
  settings["1"] = "10";
  settings["0"] = "11";

  auto res = pbap.GetHardware(deviceId, settings);
  BOOST_REQUIRE( res );

  auto piba = dynamic_cast<PiGPIOdpp::PiBOPArray*>(res.get());
  BOOST_REQUIRE( piba );

  res->Set(0, true);
  res->Set(1, true);
  BOOST_CHECK_NO_THROW( res->Update() );
}

BOOST_AUTO_TEST_SUITE_END()
