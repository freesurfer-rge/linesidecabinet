#include <boost/test/unit_test.hpp>

#include "linesideexceptions.hpp"

// ==========================================

BOOST_AUTO_TEST_SUITE(LinesideExceptions)

BOOST_AUTO_TEST_CASE(ItemIdMismatchException)
{
  Lineside::ItemId exp(1), act(2);

  Lineside::ItemIdMismatchException ime(exp, act);
  BOOST_CHECK_EQUAL( ime.expected, exp );
  BOOST_CHECK_EQUAL( ime.actual, act );

  const std::string expected = "Expected 00:00:00:01 but Got 00:00:00:02";
  BOOST_CHECK_EQUAL(expected, ime.what());
}

BOOST_AUTO_TEST_CASE(KeyNotFoundException)
{
  Lineside::KeyNotFoundException knfe("myKey");
  BOOST_CHECK_EQUAL( knfe.keyName, "myKey" );

  const std::string expected = "Key 'myKey' not found";
  BOOST_CHECK_EQUAL(expected, knfe.what());
}

BOOST_AUTO_TEST_CASE(DuplicateKeyException)
{
  Lineside::DuplicateKeyException dke("myKey");
  BOOST_CHECK_EQUAL( dke.keyName, "myKey" );

  const std::string expected = "Key 'myKey' already present";
  BOOST_CHECK_EQUAL(expected, dke.what());
}

BOOST_AUTO_TEST_SUITE_END()
