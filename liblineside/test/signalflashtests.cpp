#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include <sstream>

#include "lineside/signalflash.hpp"

char const* flashNames[] = { "Steady", "Flashing" };
Lineside::SignalFlash flashes[] = { Lineside::SignalFlash::Steady,
				    Lineside::SignalFlash::Flashing };

auto nameToFlashZip = boost::unit_test::data::make(flashNames)
  ^ boost::unit_test::data::make(flashes);

BOOST_AUTO_TEST_SUITE( SignalFlash )

BOOST_DATA_TEST_CASE( ToString, nameToFlashZip, name, flash )
{
  BOOST_CHECK_EQUAL( name, Lineside::ToString(flash) );
}

BOOST_DATA_TEST_CASE( StreamInsertion, nameToFlashZip, name, flash )
{
  std::stringstream res;
  res << flash;
  BOOST_CHECK_EQUAL( res.str(), name );
}

BOOST_DATA_TEST_CASE( Parse, nameToFlashZip, name, flash )
{
  BOOST_CHECK_EQUAL( flash, Lineside::Parse<Lineside::SignalFlash>(name) );
}

BOOST_AUTO_TEST_CASE( BadParse )
{
  const std::string badString = "SomeRandomString";

  const std::string expected = "Could not parse 'SomeRandomString' to SignalFlash";
  BOOST_CHECK_EXCEPTION( Lineside::Parse<Lineside::SignalFlash>(badString),
			 std::invalid_argument,
			 [=](const std::invalid_argument& ia) {
			   BOOST_CHECK_EQUAL( expected, ia.what() );
			   return expected == ia.what();
			 });
}

BOOST_AUTO_TEST_SUITE_END()
