#include <boost/test/unit_test.hpp>

#include "tendril/mocks/mockboparray.hpp"

BOOST_AUTO_TEST_SUITE(MockBOPArray)

BOOST_AUTO_TEST_CASE( SetAndUpdate )
{
  Tendril::Mocks::MockBOPArray mba(2);

  BOOST_CHECK_EQUAL( mba.outputs.at(0), false );
  BOOST_CHECK_EQUAL( mba.outputs.at(1), false );

  mba.Set(0, true);
  BOOST_CHECK_EQUAL( mba.outputs.at(0), false );
  BOOST_CHECK_EQUAL( mba.outputs.at(1), false );

  mba.Update();
  BOOST_CHECK_EQUAL( mba.outputs.at(0), true );
  BOOST_CHECK_EQUAL( mba.outputs.at(1), false );

  mba.Set(1, true);
  mba.Set(0, false);
  BOOST_CHECK_EQUAL( mba.outputs.at(0), true );
  BOOST_CHECK_EQUAL( mba.outputs.at(1), false );

  mba.Update();
  BOOST_CHECK_EQUAL( mba.outputs.at(0), false );
  BOOST_CHECK_EQUAL( mba.outputs.at(1), true );
}

BOOST_AUTO_TEST_SUITE_END()
