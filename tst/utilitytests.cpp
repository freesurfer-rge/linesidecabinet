#include <set>

#include <boost/test/unit_test.hpp>

#include "utility.hpp"

BOOST_AUTO_TEST_SUITE(Utility)

BOOST_AUTO_TEST_SUITE(Lock_Or_Throw)

BOOST_AUTO_TEST_CASE(Successful)
{
  const int anyInt = 10;
  auto myInt = std::make_shared<int>(anyInt);

  BOOST_CHECK( myInt );
  BOOST_CHECK_EQUAL( *myInt, anyInt );
  BOOST_CHECK_EQUAL( myInt.use_count(), 1 );

  auto wp = std::weak_ptr<int>(myInt);
  BOOST_CHECK_EQUAL( wp.use_count(), 1 );

  LOCK_OR_THROW( sp, wp );

  BOOST_CHECK_EQUAL( myInt.use_count(), 2 );
  BOOST_CHECK_EQUAL( wp.use_count(), 2 );
  BOOST_CHECK_EQUAL( *sp, *myInt );
  BOOST_CHECK_EQUAL( sp.get(), myInt.get() );
}

BOOST_AUTO_TEST_CASE(Failure)
{
  auto wp = std::weak_ptr<int>();
  BOOST_CHECK( wp.expired() );

  {
    const int anyInt = 10;
    auto myInt = std::make_shared<int>(anyInt);

    wp = myInt;
    BOOST_CHECK( !wp.expired() );
    BOOST_CHECK_EQUAL( wp.use_count(), 1 );
  }

  BOOST_CHECK( wp.expired() );

  BOOST_CHECK_EXCEPTION( LOCK_OR_THROW( sp, wp ),
			 Lineside::PointerLockFailureException,
			 [&](const Lineside::PointerLockFailureException& e) {
			   /* 
			      The exact line number in the exception can vary with compiler.
			      It appears that Clang picks the first line of the
			      BOOST_CHECK_EXCEPTION statement while gcc picks the last
			   */
			   std::set<unsigned int> possibleLines({ 47, 64 });
			   BOOST_TEST_INFO("Reported line number " << e.linenumber );
			   BOOST_CHECK_EQUAL( possibleLines.count(e.linenumber), 1 );
			   BOOST_TEST_INFO("Reported filename " << e.filename );
			   BOOST_CHECK_NE( e.filename.find("utilitytests.cpp"),
					   std::string::npos );

			   return true;
			 } );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
