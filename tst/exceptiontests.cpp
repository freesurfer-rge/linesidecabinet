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

BOOST_AUTO_TEST_CASE(PointerLockFailureException)
{
  Lineside::PointerLockFailureException plfe(__FILE__, __LINE__);
  // The __FILE__ macro is expanding to the full path
  BOOST_CHECK_NE( plfe.filename.find("exceptiontests.cpp"), std::string::npos );
  BOOST_CHECK_EQUAL( plfe.linenumber, 23 );
}

BOOST_AUTO_TEST_CASE(BadPWItemDataException)
{
  const Lineside::ItemId id(1);
  const std::string info("Some information");

  Lineside::BadPWItemDataException bpde(id, info);

  BOOST_CHECK_EQUAL( bpde.item, id );
  const std::string expected = "Configuration problem for 00:00:00:01 - Some information";
  BOOST_CHECK_EQUAL( expected, bpde.what() );
}

BOOST_AUTO_TEST_CASE(DeviceRequestException)
{
  const std::string ctrl("A");
  const std::string ctrlData("BC");
  const std::string issue("DEF");

  Lineside::DeviceRequestException dre(ctrl, ctrlData, issue);
  BOOST_CHECK_EQUAL( dre.controller, ctrl );
  BOOST_CHECK_EQUAL( dre.controllerData, ctrlData );
  BOOST_CHECK_EQUAL( dre.issueDescription, issue );
  const std::string expected = "Something";
  BOOST_CHECK_EQUAL( expected, dre.what() );
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

BOOST_AUTO_TEST_CASE(InvalidStateException)
{
  const Lineside::ItemId id(256);
  const std::string stateInfo("Something or other");

  Lineside::InvalidStateException ise( id, stateInfo );
  BOOST_CHECK_EQUAL( ise.target, id );
  BOOST_CHECK_EQUAL( ise.info, stateInfo );

  const std::string expected = "Invalid state for 00:00:01:00. State was: Something or other";
  BOOST_CHECK_EQUAL( ise.what(), expected );
}

BOOST_AUTO_TEST_SUITE_END()
