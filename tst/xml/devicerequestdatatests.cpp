#include <boost/test/unit_test.hpp>

#include <memory>

#include <xercesc/parsers/XercesDOMParser.hpp>

#include "xmlutils.hpp"

#include "xml/xercesguard.hpp"
#include "xml/utilities.hpp"
#include "xml/devicerequestdatareader.hpp"

// ================================

const std::string binaryinputFragment = "devicerequest-binaryinput.xml";
const std::string binaryoutputFragment = "devicerequest-binaryoutput.xml";
const std::string pwmchannelFragment = "devicerequest-pwmchannel.xml";

// ================================

BOOST_AUTO_TEST_SUITE( xml )

BOOST_AUTO_TEST_SUITE( DeviceRequestDataReader )

BOOST_AUTO_TEST_CASE( SmokeBinaryInput )
{
  Lineside::xml::XercesGuard xg;
  auto parser = GetParser();

  auto rootElement = GetRootElementOfFile(parser, binaryinputFragment);
  BOOST_REQUIRE(rootElement);

  auto binaryInputElement = Lineside::xml::GetSingleElementByName(rootElement, "BinaryInput" );
  BOOST_REQUIRE( binaryInputElement );

  Lineside::xml::DeviceRequestDataReader reader;

  auto result = reader.Read(binaryInputElement);
  BOOST_CHECK_EQUAL( result.controller, "GPIO" );
  BOOST_CHECK_EQUAL( result.controllerData, "100" );
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

  Lineside::xml::DeviceRequestDataReader reader;

  auto result = reader.Read(binaryOutputElement);
  BOOST_CHECK_EQUAL( result.controller, "GPIO" );
  BOOST_CHECK_EQUAL( result.controllerData, "100" );
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

  Lineside::xml::DeviceRequestDataReader reader;

  auto result = reader.Read(pwmChannelElement);
  BOOST_CHECK_EQUAL( result.controller, "sc01" );
  BOOST_CHECK_EQUAL( result.controllerData, "01" );
  BOOST_REQUIRE_EQUAL( result.settings.size(), 0 );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
