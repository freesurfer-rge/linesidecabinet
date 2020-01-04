#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include <sstream>

#include "signalstate.hpp"

char const* names[] = { "Red", "DoubleYellow", "Yellow", "Green" };
Lineside::SignalState states[] = { Lineside::SignalState::Red,
				   Lineside::SignalState::DoubleYellow,
				   Lineside::SignalState::Yellow,
				   Lineside::SignalState::Green };

BOOST_AUTO_TEST_SUITE( SignalState )


BOOST_DATA_TEST_CASE( ToString,
		      boost::unit_test::data::make(names)^boost::unit_test::data::make(states),
		      name,
		      state )
{
  BOOST_CHECK_EQUAL( name, Lineside::ToString(state) );
}

BOOST_DATA_TEST_CASE( StreamInsertion,
		      boost::unit_test::data::make(names)^boost::unit_test::data::make(states),
		      name,
		      state )
{
  std::stringstream res;
  res << state;
  BOOST_CHECK_EQUAL( res.str(), name );
}


BOOST_AUTO_TEST_SUITE_END()
