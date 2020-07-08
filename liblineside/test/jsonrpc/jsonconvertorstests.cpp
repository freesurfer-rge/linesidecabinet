#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "lineside/jsonrpc/jsonconvertors.hpp"

BOOST_AUTO_TEST_SUITE( jsonrpc )

BOOST_AUTO_TEST_SUITE( jsonconvertors )

BOOST_AUTO_TEST_CASE( ItemId )
{
  const std::string idStr = "00:02:39:d3";
  Lineside::ItemId id;
  id.Parse(idStr);

  nlohmann::json j = id;

  std::string jsonString = j.dump();
  BOOST_CHECK_EQUAL( jsonString, "\"" + idStr + "\"" );

  auto id2 = j.get<Lineside::ItemId>();
  BOOST_CHECK_EQUAL( id, id2 );
}

BOOST_DATA_TEST_CASE( SignalState,
		      boost::unit_test::data::make(
						   {
						    Lineside::SignalState::Red,
						    Lineside::SignalState::DoubleYellow,
						    Lineside::SignalState::Yellow,
						    Lineside::SignalState::Green
						   }),
		      state )
{
  std::string expected = "\"" + ToString(state) + "\"";

  nlohmann::json j = state;
  BOOST_CHECK_EQUAL( j.dump(), expected );

  auto state2 = j.get<Lineside::SignalState>();
  BOOST_CHECK_EQUAL( state, state2 );
}

BOOST_DATA_TEST_CASE( SignalFlash,
		      boost::unit_test::data::make(
						   {
						    Lineside::SignalFlash::Steady,
						    Lineside::SignalFlash::Flashing
						   }),
		      flash )
{
  std::string expected = "\"" + ToString(flash) + "\"";

  nlohmann::json j = flash;
  BOOST_CHECK_EQUAL( j.dump(), expected );

  auto flash2 = j.get<Lineside::SignalFlash>();
  BOOST_CHECK_EQUAL( flash, flash2 );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
