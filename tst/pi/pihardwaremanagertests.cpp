#include <boost/test/unit_test.hpp>

#include "pi/pihardwaremanager.hpp"

BOOST_AUTO_TEST_SUITE( pi )

BOOST_AUTO_TEST_SUITE( PiHardwareManager )

BOOST_AUTO_TEST_CASE( SmokeOutputPin )
{
  Lineside::HardwareManagerData hmd;

  Lineside::Pi::PiHardwareManager pi(hmd);

  auto bopProvider = pi.bopProviderRegistrar.Retrieve("GPIO");
  BOOST_REQUIRE( bopProvider );
  
  std::string pinId = "5";
  auto settings = std::map<std::string,std::string>();

  auto pin = bopProvider->GetHardware( pinId, settings );
  BOOST_REQUIRE(pin);
  // Should start with pin in off state
  BOOST_CHECK_EQUAL( pin->Get(), false );

  auto gpbop = dynamic_cast<Lineside::Pi::GPOutput*>(pin.get());
  BOOST_REQUIRE(gpbop);
}

BOOST_AUTO_TEST_CASE( SmokeInputPin )
{
  Lineside::HardwareManagerData hmd;
  Lineside::Pi::PiHardwareManager pi(hmd);

  auto bipProvider = pi.bipProviderRegistrar.Retrieve("GPIO");
  BOOST_REQUIRE( bipProvider );
  
  std::string pinId = "5";
  auto settings = std::map<std::string,std::string>();
  settings["pud"] = "Down";

  auto pin = bipProvider->GetHardware( pinId, settings );
  BOOST_REQUIRE(pin);
  // With the pulldown resistor, expect the pin to be off
  BOOST_CHECK_EQUAL( pin->Get(), false );

  auto gpbip = dynamic_cast<Lineside::Pi::GPInput*>(pin.get());
  BOOST_REQUIRE(gpbip);
}

BOOST_AUTO_TEST_CASE( CheckGPIODevice )
{
  Lineside::HardwareManagerData hmd;

  Lineside::Pi::PiHardwareManager pi(hmd);

  BOOST_CHECK_EQUAL( pi.GPIO, "GPIO" );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
