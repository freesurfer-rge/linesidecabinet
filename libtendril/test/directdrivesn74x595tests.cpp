#include <boost/test/unit_test.hpp>

#include "tendril/mocks/mockbop.hpp"

#include "tendril/devices/directdrivesn74x595.hpp"
#include "tendril/devices/boparray595.hpp"

BOOST_AUTO_TEST_SUITE(DirectDriveSN74x595)

BOOST_AUTO_TEST_CASE(Smoke)
{
  const std::string name = "My595";
  const unsigned int chips = 1;
  std::unique_ptr<Tendril::BinaryOutputPin> clkPin = std::make_unique<Tendril::Mocks::MockBOP>();
  std::unique_ptr<Tendril::BinaryOutputPin> datPin = std::make_unique<Tendril::Mocks::MockBOP>();
  std::unique_ptr<Tendril::BinaryOutputPin> lthPin = std::make_unique<Tendril::Mocks::MockBOP>();
  std::unique_ptr<Tendril::BinaryOutputPin> enbPin = std::make_unique<Tendril::Mocks::MockBOP>();
  std::unique_ptr<Tendril::BinaryOutputPin> clrPin = std::make_unique<Tendril::Mocks::MockBOP>();

  auto clrPtr = dynamic_cast<Tendril::Mocks::MockBOP*>(clrPin.get());
  BOOST_REQUIRE( clrPtr );
  
  auto sn595 = std::make_shared<Tendril::Devices::DirectDriveSN74x595>(name,
								       chips,
								       clkPin,
								       datPin,
								       lthPin,
								       enbPin,
								       clrPin);
  BOOST_REQUIRE(sn595);
  // Check the clear pin was set high
  BOOST_CHECK_EQUAL( clrPtr->lastLevel, true );

  // Check that two of the functions work
  sn595->Reset();
  sn595->EnableOutputs(true);

  // Try getting a BOPArray
  const std::string arrayId = "SomeArray";
  Tendril::SettingsMap arraySettings;
  arraySettings["0"] = "7";
  arraySettings["1"] = "2";

  auto bopArray = sn595->GetHardware(arrayId, arraySettings);
  BOOST_REQUIRE( bopArray );
  auto boparray595 = dynamic_cast<Tendril::Devices::BOPArray595*>(bopArray.get());
  BOOST_REQUIRE( boparray595 );

  // Set something, and make sure that it at least doesn't throw any exceptions
  bopArray->Set(0, true);
  bopArray->Set(1, false);
  bopArray->Update();
}

BOOST_AUTO_TEST_CASE(SmokeNoEnableClear)
{
   const std::string name = "My595";
  const unsigned int chips = 2;
  std::unique_ptr<Tendril::BinaryOutputPin> clkPin = std::make_unique<Tendril::Mocks::MockBOP>();
  std::unique_ptr<Tendril::BinaryOutputPin> datPin = std::make_unique<Tendril::Mocks::MockBOP>();
  std::unique_ptr<Tendril::BinaryOutputPin> lthPin = std::make_unique<Tendril::Mocks::MockBOP>();
  std::unique_ptr<Tendril::BinaryOutputPin> enbPin;
  std::unique_ptr<Tendril::BinaryOutputPin> clrPin;

  
  auto sn595 = std::make_shared<Tendril::Devices::DirectDriveSN74x595>(name,
								       chips,
								       clkPin,
								       datPin,
								       lthPin,
								       enbPin,
								       clrPin);
  BOOST_REQUIRE(sn595);

  // Don't have the enable and clear pins, so expect some exceptions
  BOOST_CHECK_THROW( sn595->Reset(), std::logic_error );
  BOOST_CHECK_THROW( sn595->EnableOutputs(false), std::logic_error );
  

  // Try getting a BOPArray
  const std::string arrayId = "SomeArray";
  Tendril::SettingsMap arraySettings;
  arraySettings["0"] = "15";
  arraySettings["1"] = "2";
  arraySettings["2"] = "5";

  auto bopArray = sn595->GetHardware(arrayId, arraySettings);
  BOOST_REQUIRE( bopArray );
  auto boparray595 = dynamic_cast<Tendril::Devices::BOPArray595*>(bopArray.get());
  BOOST_REQUIRE( boparray595 );

  // Set something, and make sure that it at least doesn't throw any exceptions
  bopArray->Set(0, true);
  bopArray->Set(1, false);
  bopArray->Set(2, true);
  bopArray->Update();
}

BOOST_AUTO_TEST_SUITE_END()
