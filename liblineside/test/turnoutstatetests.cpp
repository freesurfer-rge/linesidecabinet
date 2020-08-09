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

BOOST_AUTO_TEST_SUITE_END()
