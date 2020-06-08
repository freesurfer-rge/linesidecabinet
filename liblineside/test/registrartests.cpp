#include <sstream>

#include <boost/test/unit_test.hpp>

#include "lineside/registrar.hpp"

// ==========================================

BOOST_AUTO_TEST_SUITE(Registrar)

BOOST_AUTO_TEST_CASE(RegisterAndRetrieve)
{
  const std::string name = "Sample";
  const int myVal = 3;
  Lineside::Registrar<int> hpr;

  std::shared_ptr<int> myInt = std::make_shared<int>(myVal);
  BOOST_CHECK( myInt.unique() );

  hpr.Register(name, myInt);
  BOOST_CHECK_EQUAL( myInt.use_count(), 2 );
  auto res = hpr.Retrieve(name);

  BOOST_CHECK_EQUAL( res, myInt );
  BOOST_CHECK_EQUAL( *res, myVal );
}

BOOST_AUTO_TEST_CASE(RegisterTwoAndRetrieve)
{
  const std::string n1 = "First";
  const std::string n2 = "Second";
  const int val1 = 3;
  const int val2 = 4;

  Lineside::Registrar<int> hpr;

  std::shared_ptr<int> i1 = std::make_shared<int>(val1);
  std::shared_ptr<int> i2 = std::make_shared<int>(val2);

  hpr.Register(n1, i1);
  hpr.Register(n2, i2);

  auto res1 = hpr.Retrieve(n1);
  auto res2 = hpr.Retrieve(n2);

  BOOST_CHECK_EQUAL( i1, res1 );
  BOOST_CHECK_EQUAL( i2, res2 );
  BOOST_CHECK_EQUAL( val1, *res1 );
  BOOST_CHECK_EQUAL( val2, *res2 );
}

BOOST_AUTO_TEST_CASE(ExceptionOnMissingKey)
{
  Lineside::Registrar<int> hpr;

  const std::string name = "Something";
  BOOST_CHECK_EXCEPTION( hpr.Retrieve(name),
			 Lineside::KeyNotFoundException,
			 [&](const Lineside::KeyNotFoundException& e) {
			   return e.keyName == name;
			 } );
}

BOOST_AUTO_TEST_CASE(ExceptionOnDuplicateKey)
{
  Lineside::Registrar<int> hpr;

  const std::string name = "AnotherThing";

  std::shared_ptr<int> i1 = std::make_shared<int>(3);
  std::shared_ptr<int> i2 = std::make_shared<int>(4);

  hpr.Register(name, i1);
  BOOST_CHECK_EXCEPTION( hpr.Register(name, i2),
			 Lineside::DuplicateKeyException,
			 [&](const Lineside::DuplicateKeyException& e) {
			   return e.keyName == name;
			 } );
}

BOOST_AUTO_TEST_SUITE_END()
