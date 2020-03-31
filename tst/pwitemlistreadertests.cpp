#include <boost/test/unit_test.hpp>

#include <memory>

#include <xercesc/parsers/XercesDOMParser.hpp>

#include "xmlutils.hpp"

#include "xml/xercesguard.hpp"
#include "xml/utilities.hpp"

#include "xml/pwitemlistreader.hpp"

#include "servoturnoutmotordata.hpp"
#include "trackcircuitmonitordata.hpp"
#include "multiaspectsignalheaddata.hpp"

// ====================

const std::string pwitemlistFragment = "pwitemlist.xml";

// ====================

BOOST_AUTO_TEST_SUITE( PWItemListReader )

BOOST_AUTO_TEST_CASE( SmokePWItemListReader )
{
  Lineside::xml::XercesGuard xg;
  auto parser = GetParser();

  auto rootElement = GetRootElementOfFile(parser, pwitemlistFragment);
  BOOST_REQUIRE(rootElement);

  Lineside::xml::PWItemListReader reader;
  auto listElement = reader.GetPWItemListElement(rootElement);
  BOOST_REQUIRE(listElement);

  BOOST_FAIL("To be completed");
}

BOOST_AUTO_TEST_SUITE_END()
