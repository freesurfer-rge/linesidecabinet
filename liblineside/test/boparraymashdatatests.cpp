#include <boost/test/unit_test.hpp>

#include "lineside/boparraymashdata.hpp"
#include "lineside/linesideexceptions.hpp"

#include "exceptionmessagecheck.hpp"

BOOST_AUTO_TEST_SUITE(BOPArrayMASHData)

// ---------------

BOOST_AUTO_TEST_SUITE(ExtractAspects)

BOOST_AUTO_TEST_CASE(TwoAspect)
{
  Lineside::BOPArrayMASHData mashd;
  mashd.id = 16;

  mashd.settings["Green"] = "0";
  mashd.settings["Red"] = "1";
  mashd.settings["Feather1"] = "2";

  auto result = mashd.ExtractAspects();
  BOOST_REQUIRE_EQUAL( result.size(), 2 );
  BOOST_CHECK_EQUAL( result.at(Lineside::SignalAspect::Red), 1 );
  BOOST_CHECK_EQUAL( result.at(Lineside::SignalAspect::Green), 0 );
}

BOOST_AUTO_TEST_CASE(ThreeAspect)
{
  Lineside::BOPArrayMASHData mashd;
  mashd.id = 19;

  mashd.settings["Green"] = "0";
  mashd.settings["Yellow1"] = "3";
  mashd.settings["Red"] = "1";
  mashd.settings["Feather1"] = "2";

  auto result = mashd.ExtractAspects();
  BOOST_REQUIRE_EQUAL( result.size(), 3 );
  BOOST_CHECK_EQUAL( result.at(Lineside::SignalAspect::Red), 1 );
  BOOST_CHECK_EQUAL( result.at(Lineside::SignalAspect::Green), 0 );
  BOOST_CHECK_EQUAL( result.at(Lineside::SignalAspect::Yellow1), 3 );
}

BOOST_AUTO_TEST_CASE(FourAspect)
{
  Lineside::BOPArrayMASHData mashd;
  mashd.id = 19;

  mashd.settings["Green"] = "4";
  mashd.settings["Yellow1"] = "3";
  mashd.settings["Yellow2"] = "2";
  mashd.settings["Red"] = "1";
  mashd.settings["Feather1"] = "0";

  auto result = mashd.ExtractAspects();
  BOOST_REQUIRE_EQUAL( result.size(), 4 );
  BOOST_CHECK_EQUAL( result.at(Lineside::SignalAspect::Red), 1);
  BOOST_CHECK_EQUAL( result.at(Lineside::SignalAspect::Green), 4 );
  BOOST_CHECK_EQUAL( result.at(Lineside::SignalAspect::Yellow1), 3 );
  BOOST_CHECK_EQUAL( result.at(Lineside::SignalAspect::Yellow2), 2 );
}

BOOST_AUTO_TEST_CASE(NoRedAspect)
{
  Lineside::BOPArrayMASHData mashd;
  mashd.id = 16;

  mashd.settings["Green"] = "0";
  std::string msg = "Configuration problem for 00:00:00:10 - Red aspect missing";
  BOOST_CHECK_EXCEPTION( mashd.ExtractAspects(),
			 Lineside::BadPWItemDataException,
			 GetExceptionMessageChecker<Lineside::BadPWItemDataException>(msg) );
}

BOOST_AUTO_TEST_CASE(NoGreenAspect)
{
  Lineside::BOPArrayMASHData mashd;
  mashd.id = 17;

  mashd.settings["Red"] = "0";
  std::string msg = "Configuration problem for 00:00:00:11 - Green aspect missing";
  BOOST_CHECK_EXCEPTION( mashd.ExtractAspects(),
			 Lineside::BadPWItemDataException,
			 GetExceptionMessageChecker<Lineside::BadPWItemDataException>(msg) );
}

BOOST_AUTO_TEST_CASE(Yellow2AspectButNoYellow1)
{
  Lineside::BOPArrayMASHData mashd;
  mashd.id = 35;

  mashd.settings["Red"] = "0";
  mashd.settings["Green"] = "2";
  mashd.settings["Yellow2"] = "1";
  std::string msg = "Configuration problem for 00:00:00:23 - Have Yellow2 aspect but no Yellow1";
  BOOST_CHECK_EXCEPTION( mashd.ExtractAspects(),
			 Lineside::BadPWItemDataException,
			 GetExceptionMessageChecker<Lineside::BadPWItemDataException>(msg) );

}

BOOST_AUTO_TEST_SUITE_END()

// ---------------

BOOST_AUTO_TEST_SUITE_END()
