#include <boost/test/unit_test.hpp>

#include "tendril/mocks/mocki2ccommunicator.hpp"

BOOST_AUTO_TEST_SUITE(MockI2CCommunicator)

BOOST_AUTO_TEST_CASE( WriteByte )
{
  Tendril::Mocks::MockI2CCommunicator mi2c;

  BOOST_CHECK_EQUAL( mi2c.lastRegister, 0 );
  BOOST_CHECK_EQUAL( mi2c.lastWrite, 0 );

  mi2c.WriteByte(10, 11);
  BOOST_CHECK_EQUAL( mi2c.lastRegister, 10 );
  BOOST_CHECK_EQUAL( mi2c.lastWrite, 11 );
}

BOOST_AUTO_TEST_CASE( WriteWord )
{
  Tendril::Mocks::MockI2CCommunicator mi2c;

  BOOST_CHECK_EQUAL( mi2c.lastRegister, 0 );
  BOOST_CHECK_EQUAL( mi2c.lastWrite, 0 );

  mi2c.WriteWord(10, 4096);
  BOOST_CHECK_EQUAL( mi2c.lastRegister, 10 );
  BOOST_CHECK_EQUAL( mi2c.lastWrite, 4096 );
}

BOOST_AUTO_TEST_SUITE_END()
