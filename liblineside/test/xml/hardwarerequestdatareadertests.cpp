#include <boost/test/unit_test.hpp>

#include <memory>

#include <xercesc/parsers/XercesDOMParser.hpp>

#include "xmlutils.hpp"

#include "lineside/xml/xercesguard.hpp"
#include "lineside/xml/utilities.hpp"
#include "lineside/xml/hardwarerequestdatareader.hpp"

// ================================

const std::string binaryinputFragment = "hardwarerequest-binaryinput.xml";
const std::string binaryoutputFragment = "hardwarerequest-binaryoutput.xml";
const std::string pwmchannelFragment = "hardwarerequest-pwmchannel.xml";
const std::string boparrayFragment = "hardwarerequest-boparray.xml";

// ================================

BOOST_AUTO_TEST_SUITE( xml )

BOOST_AUTO_TEST_SUITE( HardwareRequestDataReader )

BOOST_AUTO_TEST_CASE( SmokeBinaryInput )
{
  Lineside::xml::XercesGuard xg;
  auto parser = GetParser();

  auto rootElement = GetRootElementOfFile(parser, binaryinputFragment);
  BOOST_REQUIRE(rootElement);

  auto binaryInputElement = Lineside::xml::GetSingleElementByName(rootElement, "BinaryInput" );
  BOOST_REQUIRE( binaryInputElement );

  Lineside::xml::HardwareRequestDataReader reader;

  auto result = reader.Read(binaryInputElement);
  BOOST_CHECK_EQUAL( result.providerName, "GPIO" );
  BOOST_CHECK_EQUAL( result.idOnProvider, "100" );
  BOOST_REQUIRE_EQUAL( result.settings.size(), 1 );
  BOOST_CHECK_EQUAL( result.settings.at("glitch"), "10000" );
}

BOOST_AUTO_TEST_CASE( SmokeBinaryOutput )
{
  Lineside::xml::XercesGuard xg;
  auto parser = GetParser();

  auto rootElement = GetRootElementOfFile(parser, binaryoutputFragment);
  BOOST_REQUIRE(rootElement);

  auto binaryOutputElement = Lineside::xml::GetSingleElementByName(rootElement, "BinaryOutput" );
  BOOST_REQUIRE( binaryOutputElement );

  Lineside::xml::HardwareRequestDataReader reader;

  auto result = reader.Read(binaryOutputElement);
  BOOST_CHECK_EQUAL( result.providerName, "GPIO" );
  BOOST_CHECK_EQUAL( result.idOnProvider, "100" );
  BOOST_REQUIRE_EQUAL( result.settings.size(), 0 );
}

BOOST_AUTO_TEST_CASE( SmokePWMChannel )
{
  Lineside::xml::XercesGuard xg;
  auto parser = GetParser();

  auto rootElement = GetRootElementOfFile(parser, pwmchannelFragment);
  BOOST_REQUIRE(rootElement);

  auto pwmChannelElement = Lineside::xml::GetSingleElementByName(rootElement, "PWMChannel" );
  BOOST_REQUIRE( pwmChannelElement );

  Lineside::xml::HardwareRequestDataReader reader;

  auto result = reader.Read(pwmChannelElement);
  BOOST_CHECK_EQUAL( result.providerName, "sc01" );
  BOOST_CHECK_EQUAL( result.idOnProvider, "01" );
  BOOST_REQUIRE_EQUAL( result.settings.size(), 0 );
}

BOOST_AUTO_TEST_CASE( SmokeBOPArray )
{
  Lineside::xml::XercesGuard xg;
  auto parser = GetParser();

  auto rootElement = GetRootElementOfFile(parser, boparrayFragment);
  BOOST_REQUIRE(rootElement);

  auto pwmChannelElement = Lineside::xml::GetSingleElementByName(rootElement, "BOPArray" );
  BOOST_REQUIRE( pwmChannelElement );

  Lineside::xml::HardwareRequestDataReader reader;

  auto result = reader.Read(pwmChannelElement);
  BOOST_CHECK_EQUAL( result.providerName, "GPIO" );
  BOOST_CHECK_EQUAL( result.idOnProvider, "Unused" );
  BOOST_REQUIRE_EQUAL( result.settings.size(), 6 );
  BOOST_CHECK_EQUAL( result.settings.at("0"), "13" );
  BOOST_CHECK_EQUAL( result.settings.at("1"), "19" );
  BOOST_CHECK_EQUAL( result.settings.at("2"), "26" );
  BOOST_CHECK_EQUAL( result.settings.at("3"), "16" );
  BOOST_CHECK_EQUAL( result.settings.at("4"), "20" );
  BOOST_CHECK_EQUAL( result.settings.at("5"), "21" );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
