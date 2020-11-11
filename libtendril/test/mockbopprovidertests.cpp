#include <boost/test/unit_test.hpp>

#include "tendril/keyexception.hpp"
#include "tendril/mocks/mockbopprovider.hpp"

BOOST_AUTO_TEST_SUITE(MockBOPProvider)

BOOST_AUTO_TEST_CASE( CreateBOP )
{
  Tendril::Mocks::MockBOPProvider bopProvider;

  const std::string hardwareId("SomeName");
  Tendril::SettingsMap settings;
  settings["A"] = "B";

  auto bop = bopProvider.GetHardware(hardwareId, settings);
  BOOST_REQUIRE(bop);

  BOOST_CHECK_EQUAL( bopProvider.pins.size(), 1 );
  BOOST_CHECK_EQUAL( bopProvider.pins.count(hardwareId), 1 );

  // Start doing bad things with the pointer
  auto mb = dynamic_cast<Tendril::Mocks::MockBOP*>(bop.get());
  BOOST_REQUIRE(mb);
  BOOST_CHECK_EQUAL( mb, bopProvider.pins.at(hardwareId) );
  BOOST_CHECK_EQUAL( mb->settings.size(), settings.size() );
  BOOST_CHECK_EQUAL( mb->settings.at("A"), settings.at("A") );
}

BOOST_AUTO_TEST_CASE( NoDuplicates )
{
  Tendril::Mocks::MockBOPProvider bopProvider;

  const std::string hardwareId("SomeName");
  Tendril::SettingsMap settings;
  
  auto bop = bopProvider.GetHardware(hardwareId, settings);
  BOOST_REQUIRE(bop);

  BOOST_CHECK_EXCEPTION( bopProvider.GetHardware(hardwareId, settings),
			 Tendril::DuplicateKeyException,
			 [=](const Tendril::DuplicateKeyException& dke) {
			   return dke.keyName == hardwareId;
			 });
}

BOOST_AUTO_TEST_SUITE_END()
