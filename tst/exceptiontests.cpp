#include <boost/test/unit_test.hpp>

#include "linesideexceptions.hpp"

// ==========================================

BOOST_AUTO_TEST_SUITE(LinesideExceptions)

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
