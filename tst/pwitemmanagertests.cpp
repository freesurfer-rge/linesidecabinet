#include <boost/test/unit_test.hpp>

#include "multiaspectsignalheaddata.hpp"
#include "multiaspectsignalhead.hpp"


#include "pwitemmanager.hpp"

#include "mockmanagerfixture.hpp"

#include "exceptionmessagecheck.hpp"

// ======================================

BOOST_FIXTURE_TEST_SUITE(PWItemManager, MockManagerFixture)

BOOST_AUTO_TEST_CASE(SingleMASH)
{
  Lineside::PWItemManager im(this->hwManager, this->swManager);
  BOOST_FAIL("Need to implement");
}

BOOST_AUTO_TEST_SUITE_END()
