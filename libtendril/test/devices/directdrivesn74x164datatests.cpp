#include <boost/test/unit_test.hpp>

#include "tendril/mocks/utilities.hpp"
#include "tendril/mocks/mockbop.hpp"
#include "tendril/mocks/mockhardwareprovider.hpp"

#include "tendril/devices/directdrivesn74x164.hpp"
#include "tendril/devices/directdrivesn74x164data.hpp"

BOOST_AUTO_TEST_SUITE(Devices)

BOOST_AUTO_TEST_SUITE(DirectDriveSN74x164Data)

BOOST_AUTO_TEST_CASE(ConstructAndRegister)
{
  auto hw = Tendril::Mocks::GetMockHardwareManager();

  // Set up a basic set of data
  Tendril::Devices::DirectDriveSN74x164Data target;
  target.clockPin.providerName = Tendril::Mocks::BOPProviderId;
  target.clockPin.idOnProvider = "01";
  target.dataPin.providerName = Tendril::Mocks::BOPProviderId;
  target.dataPin.idOnProvider = "03";
  target.clearPin.providerName = Tendril::Devices::NotConnected;
  target.settings["chainLength"] = "1";
  const std::string devName = "MySR";
  target.name = devName;

  BOOST_TEST_CHECKPOINT("Data entered");

  // Create and register the chain
  target.ConstructAndRegister(*hw);

  // Now check that we can get it
  auto bapProvider = hw->bopArrayProviderRegistrar.Retrieve(devName);
  BOOST_REQUIRE(bapProvider);
  auto dd164 = std::dynamic_pointer_cast<Tendril::Devices::DirectDriveSN74x164>(bapProvider);
  BOOST_REQUIRE(dd164);
  
  // See if the pins were taken
  auto bopprovider = hw->bopProviderRegistrar.Retrieve(Tendril::Mocks::BOPProviderId);
  BOOST_REQUIRE(bopprovider);
  auto mockbopprovider = std::dynamic_pointer_cast<
    Tendril::Mocks::MockHardwareProvider<Tendril::BinaryOutputPin,Tendril::Mocks::MockBOP>
    >(bopprovider);
  BOOST_REQUIRE(mockbopprovider);
  BOOST_CHECK_EQUAL( mockbopprovider->hardware.size(), 2 );
  BOOST_CHECK_NO_THROW( mockbopprovider->hardware.at("01") );
  BOOST_CHECK_NO_THROW( mockbopprovider->hardware.at("03") );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
