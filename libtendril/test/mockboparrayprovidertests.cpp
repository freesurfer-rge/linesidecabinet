#include <boost/test/unit_test.hpp>

#include "tendril/keyexception.hpp"
#include "tendril/mocks/mockboparrayprovider.hpp"

BOOST_AUTO_TEST_SUITE(MockBOPArrayProvider)

BOOST_AUTO_TEST_CASE( CreateHardware )
{
  Tendril::Mocks::MockBOPArrayProvider provider;

  const std::string hardwareId("Something");
  Tendril::SettingsMap settings;
  settings["0"] = "GPIO34";
  settings["1"] = "GPIO02";

  auto bopArray = provider.GetHardware(hardwareId, settings);
  BOOST_REQUIRE(bopArray);
  
  BOOST_CHECK_EQUAL( provider.hardware.size(), 1 );
  BOOST_CHECK_EQUAL( provider.hardware.count(hardwareId), 1 );

  // Do bad things with a pointer
  auto mba = dynamic_cast<Tendril::Mocks::MockBOPArray*>(bopArray.get());
  BOOST_REQUIRE( mba );
  BOOST_CHECK_EQUAL( mba, provider.hardware.at(hardwareId) );
  BOOST_CHECK_EQUAL( mba->outputs.size(), 2 );
  BOOST_CHECK_EQUAL( mba->settings.size(), 2 );
  BOOST_CHECK_EQUAL( mba->settings.at("0"), "GPIO34" );
  BOOST_CHECK_EQUAL( mba->settings.at("1"), "GPIO02" );
}

BOOST_AUTO_TEST_CASE( NoDuplicates )
{
  Tendril::Mocks::MockBOPArrayProvider provider;

  const std::string hardwareId("Something");
  Tendril::SettingsMap settings;
  settings["0"] = "GPIO34";
  settings["1"] = "GPIO02";

  auto bopArray = provider.GetHardware(hardwareId, settings);
  BOOST_REQUIRE(bopArray);
  BOOST_CHECK_EXCEPTION( provider.GetHardware(hardwareId, settings),
			 Tendril::DuplicateKeyException,
			 [=](const Tendril::DuplicateKeyException& dke) {
			   return dke.keyName == hardwareId;
			 });
}

BOOST_AUTO_TEST_SUITE_END()
