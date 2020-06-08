#include <boost/test/unit_test.hpp>

#include "lineside/xml/xercesguard.hpp"

BOOST_AUTO_TEST_SUITE( xml )

BOOST_AUTO_TEST_SUITE( XercesGuard )

BOOST_AUTO_TEST_CASE( ConstructAndDestruct )
{
  Lineside::xml::XercesGuard g;
  BOOST_CHECK( (&g) != nullptr );
  BOOST_TEST_CHECKPOINT("Constructed");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
