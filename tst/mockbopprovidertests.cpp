#include <boost/test/unit_test.hpp>

#include "utility.hpp"

#include "mocks/mockbopprovider.hpp"
#include "exceptionmessagecheck.hpp"

BOOST_AUTO_TEST_SUITE(MockBOPProviderValidation)

BOOST_AUTO_TEST_CASE(ConstructOne)
{
  MockBOPProvider mbb;
  BOOST_CHECK_EQUAL( mbb.pins.size(), 0 );

  const std::string channelId = "01";
  const std::map<std::string,std::string> settings;

  auto wbop = mbb.GetHardware(channelId, settings);
  BOOST_CHECK_EQUAL( mbb.pins.size(), 1 );
  auto sharedFromProvider = mbb.pins.at(channelId);

  LOCK_OR_THROW( sbop, wbop );
  BOOST_CHECK_EQUAL( sbop.get(), sharedFromProvider.get() );
}

BOOST_AUTO_TEST_SUITE_END()
