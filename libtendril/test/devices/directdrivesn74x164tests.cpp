#include <boost/test/unit_test.hpp>

#include "tendril/mocks/mockbop.hpp"

#include "tendril/devices/directdrivesn74x164.hpp"
#include "tendril/devices/boparraysiposr.hpp"

BOOST_AUTO_TEST_SUITE(Devices)

BOOST_AUTO_TEST_SUITE(DirectDriveSN74x164)

BOOST_AUTO_TEST_CASE(Smoke)
{
  const std::string name = "My164";
  const unsigned int chips = 1;
  std::unique_ptr<Tendril::BinaryOutputPin> clkPin = std::make_unique<Tendril::Mocks::MockBOP>();
  std::unique_ptr<Tendril::BinaryOutputPin> datPin = std::make_unique<Tendril::Mocks::MockBOP>();
  std::unique_ptr<Tendril::BinaryOutputPin> clrPin = std::make_unique<Tendril::Mocks::MockBOP>();

  auto clrPtr = dynamic_cast<Tendril::Mocks::MockBOP*>(clrPin.get());
  BOOST_REQUIRE( clrPtr );
  
  auto sn164 = std::make_shared<Tendril::Devices::DirectDriveSN74x164>(name,
								       chips,
								       clkPin,
								       datPin,
								       clrPin);
  BOOST_REQUIRE(sn164);
  
  // Check the clear pin was set high
  BOOST_CHECK_EQUAL( clrPtr->lastLevel, true );

  // Check that two of the functions work
  sn164->Reset();

  // Try getting a BOPArray
  const std::string arrayId = "SomeArray";
  Tendril::SettingsMap arraySettings;
  arraySettings["0"] = "7";
  arraySettings["1"] = "2";

  auto bopArray = sn164->GetHardware(arrayId, arraySettings);
  BOOST_REQUIRE( bopArray );
  auto boparraysipo = dynamic_cast<Tendril::Devices::BOPArraySIPOSR*>(bopArray.get());
  BOOST_REQUIRE( boparraysipo );

  // Set something, and make sure that it at least doesn't throw any exceptions
  bopArray->Set(0, true);
  bopArray->Set(1, false);
  bopArray->Update();
}

BOOST_AUTO_TEST_CASE(SmokeNoClear)
{
   const std::string name = "My164";
  const unsigned int chips = 2;
  std::unique_ptr<Tendril::BinaryOutputPin> clkPin = std::make_unique<Tendril::Mocks::MockBOP>();
  std::unique_ptr<Tendril::BinaryOutputPin> datPin = std::make_unique<Tendril::Mocks::MockBOP>();
  std::unique_ptr<Tendril::BinaryOutputPin> clrPin;

  
  auto sn164 = std::make_shared<Tendril::Devices::DirectDriveSN74x164>(name,
								       chips,
								       clkPin,
								       datPin,
								       clrPin);
  BOOST_REQUIRE(sn164);

  // Don't have the clear pin, so expect some exception
  BOOST_CHECK_THROW( sn164->Reset(), std::logic_error );
  

  // Try getting a BOPArray
  const std::string arrayId = "SomeArray";
  Tendril::SettingsMap arraySettings;
  arraySettings["0"] = "15";
  arraySettings["1"] = "2";
  arraySettings["2"] = "5";

  auto bopArray = sn164->GetHardware(arrayId, arraySettings);
  BOOST_REQUIRE( bopArray );
  auto boparraysipo = dynamic_cast<Tendril::Devices::BOPArraySIPOSR*>(bopArray.get());
  BOOST_REQUIRE( boparraysipo );

  // Set something, and make sure that it at least doesn't throw any exceptions
  bopArray->Set(0, true);
  bopArray->Set(1, false);
  bopArray->Set(2, true);
  bopArray->Update();
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
