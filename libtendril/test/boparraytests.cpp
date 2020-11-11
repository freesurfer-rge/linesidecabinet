#include <boost/test/unit_test.hpp>

#include "tendril/boparray.hpp"

BOOST_AUTO_TEST_SUITE(BOPArray)

BOOST_AUTO_TEST_SUITE(ExtractPinList)

BOOST_AUTO_TEST_CASE(Smoke)
{
  Tendril::SettingsMap settings;
  settings["0"] = "GPIO12";
  settings["1"] = "GPIO15";

  auto result = Tendril::BOPArray::ExtractPinList(settings);
  BOOST_REQUIRE_EQUAL( result.size(), 2 );
  BOOST_CHECK_EQUAL( result.at(0), "GPIO12" );
  BOOST_CHECK_EQUAL( result.at(1), "GPIO15" );
}

BOOST_AUTO_TEST_CASE(DuplicateKey)
{
  Tendril::SettingsMap settings;
  // Note that both keys will parse to the same index
  settings["0"] = "GPIO12";
  settings["00"] = "GPIO15";

  BOOST_CHECK_THROW( Tendril::BOPArray::ExtractPinList(settings), std::logic_error );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
