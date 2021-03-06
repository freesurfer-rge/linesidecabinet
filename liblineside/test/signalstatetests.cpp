#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include <sstream>

#include "lineside/signalstate.hpp"

char const* stateNames[] = { "Red", "DoubleYellow", "Yellow", "Green" };
Lineside::SignalState states[] = { Lineside::SignalState::Red,
				   Lineside::SignalState::DoubleYellow,
				   Lineside::SignalState::Yellow,
				   Lineside::SignalState::Green };

auto nameToStateZip = boost::unit_test::data::make(stateNames)
  ^ boost::unit_test::data::make(states);

BOOST_AUTO_TEST_SUITE( SignalState )


BOOST_DATA_TEST_CASE( ToString, nameToStateZip, name, state )
{
  BOOST_CHECK_EQUAL( name, Lineside::ToString(state) );
}

BOOST_DATA_TEST_CASE( StreamInsertion, nameToStateZip, name, state )
{
  std::stringstream res;
  res << state;
  BOOST_CHECK_EQUAL( res.str(), name );
}

BOOST_DATA_TEST_CASE( Parse, nameToStateZip, name, state )
{
  BOOST_CHECK_EQUAL( state, Lineside::Parse<Lineside::SignalState>(name) );
}

BOOST_AUTO_TEST_CASE( BadParse )
{
  const std::string badString = "SomeRandomString";

  const std::string expected = "Could not parse 'SomeRandomString' to SignalState";
  BOOST_CHECK_EXCEPTION( Lineside::Parse<Lineside::SignalState>(badString),
			 std::invalid_argument,
			 [=](const std::invalid_argument& ia) {
			   BOOST_CHECK_EQUAL( expected, ia.what() );
			   return expected == ia.what();
			 });
}

BOOST_AUTO_TEST_SUITE_END()
