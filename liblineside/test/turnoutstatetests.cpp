#include <boost/test/unit_test.hpp>

#include "lineside/turnoutstate.hpp"

BOOST_AUTO_TEST_SUITE( TurnoutState )

BOOST_AUTO_TEST_CASE( ToString )
{
  Lineside::TurnoutState ts;
  std::string res;

  ts = Lineside::TurnoutState::Straight;
  res = Lineside::ToString( ts );
  BOOST_CHECK_EQUAL(res, "Straight");

  ts = Lineside::TurnoutState::Curved;
  res = Lineside::ToString( ts );
  BOOST_CHECK_EQUAL( res, "Curved" );
}

BOOST_AUTO_TEST_CASE( StreamInsertion )
{
  Lineside::TurnoutState ts;
  std::stringstream res;

  ts = Lineside::TurnoutState::Straight;
  res << ts;
  BOOST_CHECK_EQUAL( res.str(), "Straight" );
  res.str(std::string()); // Empty the stream

  ts = Lineside::TurnoutState::Curved;
  res << ts;
  BOOST_CHECK_EQUAL( res.str(), "Curved" );
  res.str(std::string());
}

BOOST_AUTO_TEST_CASE( Parse )
{
  auto straight = Lineside::Parse<Lineside::TurnoutState>("Straight");
  BOOST_CHECK_EQUAL( straight, Lineside::TurnoutState::Straight );

  auto curved = Lineside::Parse<Lineside::TurnoutState>("Curved");
  BOOST_CHECK_EQUAL( curved, Lineside::TurnoutState::Curved );
}

BOOST_AUTO_TEST_CASE( BadParse )
{
  const std::string badString = "SomeRandomString";

  const std::string expected = "Could not parse 'SomeRandomString' to TurnoutState";
  BOOST_CHECK_EXCEPTION( Lineside::Parse<Lineside::TurnoutState>(badString),
			 std::invalid_argument,
			 [=](const std::invalid_argument& ia) {
			   BOOST_CHECK_EQUAL( expected, ia.what() );
			   return expected == ia.what();
			 });
}

BOOST_AUTO_TEST_SUITE_END()
