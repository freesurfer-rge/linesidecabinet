#include <boost/test/unit_test.hpp>

#include <memory>

#include <xercesc/parsers/XercesDOMParser.hpp>

#include "xmlutils.hpp"

#include "xml/xercesguard.hpp"
#include "xml/utilities.hpp"
#include "xml/settingsreader.hpp"

// =================================

const std::string simpleSettingsFragment = "settings-fragment.xml";
const std::string simpleSettingsCommentFragment = "settings-comment-fragment.xml";

// =================================

BOOST_AUTO_TEST_SUITE( SettingsReader )

BOOST_AUTO_TEST_CASE( SmokeSimpleFragment )
{
  // Use guard to initialise library
  Lineside::xml::XercesGuard xg;

  // Configure the parser
  auto parser = GetParser();

  auto rootElement = GetRootElementOfFile(parser, simpleSettingsFragment);
  BOOST_REQUIRE(rootElement);

  Lineside::xml::SettingsReader reader;
  auto settingsElement = reader.GetSettingsElement(rootElement);
  auto result = reader.Read(settingsElement);
  BOOST_CHECK_EQUAL( result.size(), 2 );
  BOOST_CHECK_EQUAL( result.at("a"), "b" );
  BOOST_CHECK_EQUAL( result.at("1"), "2" );
}

BOOST_AUTO_TEST_CASE( SmokeSimpleFragmentWithComment )
{
  // Use guard to initialise library
  Lineside::xml::XercesGuard xg;

  // Configure the parser
  auto parser = GetParser();

  auto rootElement = GetRootElementOfFile(parser, simpleSettingsCommentFragment);
  BOOST_REQUIRE(rootElement);

  Lineside::xml::SettingsReader reader;
  auto settingsElement = reader.GetSettingsElement(rootElement);
  auto result = reader.Read(settingsElement);
  
  BOOST_CHECK_EQUAL( result.size(), 2 );
  BOOST_CHECK_EQUAL( result.at("c"), "d" );
  BOOST_CHECK_EQUAL( result.at("3"), "4" );
}

BOOST_AUTO_TEST_SUITE_END()
