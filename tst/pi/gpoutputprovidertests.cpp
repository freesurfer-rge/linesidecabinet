#include <boost/test/unit_test.hpp>

#include "pi/gpoutputprovider.hpp"

BOOST_AUTO_TEST_SUITE( pi )

BOOST_AUTO_TEST_SUITE( GPOutputProvider )

BOOST_AUTO_TEST_CASE( Smoke )
{
  std::shared_ptr<Lineside::Pi::GPOutputProvider> provider;
  
  {  
    auto pm = PiGPIOdpp::PiManager::CreatePiManager();

    auto gpioProvider = std::make_shared<Lineside::Pi::GPIOProvider>(pm);

    provider = std::make_shared<Lineside::Pi::GPOutputProvider>(gpioProvider);
  }

  BOOST_REQUIRE(provider);
}

BOOST_AUTO_TEST_CASE( GetPin )
{
  std::shared_ptr<Lineside::Pi::GPOutputProvider> provider;
  {  
    auto pm = PiGPIOdpp::PiManager::CreatePiManager();

    auto gpioProvider = std::make_shared<Lineside::Pi::GPIOProvider>(pm);

    provider = std::make_shared<Lineside::Pi::GPOutputProvider>(gpioProvider);
  }

  BOOST_REQUIRE(provider);

  std::string pinId = "5";
  auto settings = std::map<std::string,std::string>();

  auto bop = provider->GetHardware( pinId, settings );
  BOOST_REQUIRE(bop);
  // Should start with pin in off state
  BOOST_CHECK_EQUAL( bop->Get(), false );

  auto gpbop = dynamic_cast<Lineside::Pi::GPOutput*>(bop.get());
  BOOST_REQUIRE(gpbop);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
