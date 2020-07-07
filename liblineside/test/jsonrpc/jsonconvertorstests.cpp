#include <boost/test/unit_test.hpp>


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

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
