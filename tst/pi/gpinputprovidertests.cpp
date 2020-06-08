#include <boost/test/unit_test.hpp>

#include "pi/gpinputprovider.hpp"

BOOST_AUTO_TEST_SUITE( pi )

BOOST_AUTO_TEST_SUITE( GPInputProvider )

BOOST_AUTO_TEST_CASE( Smoke )
{
  std::shared_ptr<Lineside::Pi::GPInputProvider> provider;
  {
    auto pm = PiGPIOdpp::PiManager::CreatePiManager();
    
    auto gpioProvider = std::make_shared<Lineside::Pi::GPIOProvider>(pm);
    
    provider = std::make_shared<Lineside::Pi::GPInputProvider>(gpioProvider);
  }
  BOOST_REQUIRE(provider);
}

BOOST_AUTO_TEST_CASE( GetPin )
{
  std::shared_ptr<Lineside::Pi::GPInputProvider> provider;
  {
    auto pm = PiGPIOdpp::PiManager::CreatePiManager();
    
    auto gpioProvider = std::make_shared<Lineside::Pi::GPIOProvider>(pm);
    
    provider = std::make_shared<Lineside::Pi::GPInputProvider>(gpioProvider);
  }
  BOOST_REQUIRE(provider);

  std::string pinId = "5";
  auto settings = std::map<std::string,std::string>();
  settings["glitch"] = "300000";
  settings["pud"] = "Down";

  auto bip = provider->GetHardware( pinId, settings );
  BOOST_REQUIRE( bip );

  // With pulldown resistor, should always be in off state
  BOOST_CHECK_EQUAL( bip->Get(), false );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
