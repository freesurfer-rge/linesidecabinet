#include <boost/test/unit_test.hpp>

#include "tendril/keyexception.hpp"

BOOST_AUTO_TEST_SUITE(KeyException)

BOOST_AUTO_TEST_CASE( KeyNotFound )
{
  Tendril::KeyNotFoundException knf("SomeVar");

  BOOST_CHECK_EQUAL( knf.keyName, "SomeVar" );
  BOOST_CHECK_EQUAL( knf.what(), "Key 'SomeVar' not found" );
}

BOOST_AUTO_TEST_CASE( DuplicateKey )
{
  Tendril::DuplicateKeyException dk("SomeVar");

  BOOST_CHECK_EQUAL( dk.keyName, "SomeVar" );
  BOOST_CHECK_EQUAL( dk.what(), "Key 'SomeVar' already present" );
}

BOOST_AUTO_TEST_SUITE_END()
