#include <boost/test/unit_test.hpp>

#include "mocks/mockpwmchannel.hpp"

BOOST_AUTO_TEST_SUITE(MockPWMChannelValidation)

BOOST_AUTO_TEST_CASE(ConstructAndGet)
{
  MockPWMChannel mp;

  BOOST_CHECK_EQUAL( mp.Get(), 0 );
  BOOST_CHECK_EQUAL( mp.updates.size(), 0 );
}

BOOST_AUTO_TEST_CASE(SingleSet)
{
  MockPWMChannel mp;

  const unsigned int anyVal = 10;

  auto timePoint = std::chrono::high_resolution_clock::now();
  mp.Set( anyVal );

  BOOST_CHECK_EQUAL( mp.Get(), anyVal );
  BOOST_REQUIRE_EQUAL( mp.updates.size(), 1 );

  auto update0 = mp.updates.at(0);
  BOOST_CHECK_EQUAL( update0.second, anyVal );
  BOOST_CHECK( update0.first - timePoint < std::chrono::milliseconds(1) );
}

BOOST_AUTO_TEST_CASE(DoubleSet)
{
  MockPWMChannel mp;
  const unsigned int i1 = 10;
  const unsigned int i2 = i1+3;

  auto timePoint = std::chrono::high_resolution_clock::now();
  mp.Set(i1);
  mp.Set(i2);

  BOOST_CHECK_EQUAL( mp.Get(), i2 );
  BOOST_REQUIRE_EQUAL( mp.updates.size(), 2 );

  auto update0 = mp.updates.at(0);
  BOOST_CHECK_EQUAL( update0.second, i1 );
  BOOST_CHECK( update0.first - timePoint < std::chrono::milliseconds(1) );

  auto update1 = mp.updates.at(1);
  BOOST_CHECK_EQUAL( update1.second, i2 );
  BOOST_CHECK( update1.first > update0.first );
}

BOOST_AUTO_TEST_SUITE_END()
