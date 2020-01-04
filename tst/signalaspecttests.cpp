#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "signalaspect.hpp"

char const* names[] = { "Red", "DoubleYellow", "Yellow", "Green" };
Lineside::SignalAspect aspects[] = { Lineside::SignalAspect::Red,
				     Lineside::SignalAspect::DoubleYellow,
				     Lineside::SignalAspect::Yellow,
				     Lineside::SignalAspect::Green };

BOOST_AUTO_TEST_SUITE( SignalAspect )


BOOST_DATA_TEST_CASE( ToStringCheck,
		      boost::unit_test::data::make(names)^boost::unit_test::data::make(aspects),
		      name,
		      aspect )
{
  BOOST_CHECK_EQUAL( name, Lineside::ToString(aspect) );
}


BOOST_AUTO_TEST_SUITE_END()
