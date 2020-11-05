#include <boost/test/unit_test.hpp>

#include "tendril/mocks/mockbop.hpp"

BOOST_AUTO_TEST_SUITE(MockBOP)

BOOST_AUTO_TEST_CASE( Set )
{
  Tendril::Mocks::MockBOP mb;

  BOOST_CHECK_EQUAL( mb.lastLevel, false );
  mb.Set(true);
  BOOST_CHECK_EQUAL( mb.lastLevel, true );
  mb.Set(false);
  BOOST_CHECK_EQUAL( mb.lastLevel, false );
}

BOOST_AUTO_TEST_SUITE_END()
