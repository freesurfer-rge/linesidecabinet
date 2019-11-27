#include <sstream>

#include <boost/test/unit_test.hpp>

#include "registrar.hpp"

// ==========================================

BOOST_AUTO_TEST_SUITE(Registrar)

BOOST_AUTO_TEST_CASE(RegisterAndRetrieve)
{
  const std::string name = "Sample";
  Lineside::Registrar<int> hpr;

  int myInt = 3;

  hpr.Register(name, myInt);
  auto res = hpr.Retrieve(name);

  BOOST_CHECK_EQUAL( &res, &myInt );
}

BOOST_AUTO_TEST_CASE(RegisterTwoAndRetrieve)
{
  const std::string n1 = "First";
  const std::string n2 = "Second";

  Lineside::Registrar<int> hpr;

  int i1 = 3;
  int i2 = 4;

  hpr.Register(n1, i1);
  hpr.Register(n2, i2);

  int& res1 = hpr.Retrieve(n1);
  int& res2 = hpr.Retrieve(n2);

  BOOST_CHECK_EQUAL( i1, res1 );
  BOOST_CHECK_EQUAL( i2, res2 );
  BOOST_CHECK_EQUAL( &i1, &res1 );
  BOOST_CHECK_EQUAL( &i2, &res2 );
}

BOOST_AUTO_TEST_SUITE_END()
