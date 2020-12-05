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


BOOST_AUTO_TEST_SUITE(ExtractFeathers)

BOOST_AUTO_TEST_CASE(NoFeathers)
{
  Lineside::BOPArrayMASHData mashd;
  mashd.id = 255;

  mashd.settings["Red"] = "0";
  mashd.settings["Green"] = "2";

  auto result = mashd.ExtractFeathers();
  BOOST_CHECK_EQUAL( result.size(), 1 );
}

BOOST_AUTO_TEST_CASE(OneFeather)
{
  Lineside::BOPArrayMASHData mashd;
  mashd.id = 255;

  mashd.settings["Red"] = "0";
  mashd.settings["Green"] = "1";
  mashd.settings["Feather1"] = "2";

  auto result = mashd.ExtractFeathers();
  BOOST_REQUIRE_EQUAL( result.size(), 2 );
  BOOST_CHECK_EQUAL( result.at(1), 2 );
}

BOOST_AUTO_TEST_CASE(TwoFeathers)
{
  Lineside::BOPArrayMASHData mashd;
  mashd.id = 255;

  mashd.settings["Red"] = "2";
  mashd.settings["Green"] = "1";
  mashd.settings["Feather1"] = "0";
  mashd.settings["Feather2"] = "3";

  auto result = mashd.ExtractFeathers();
  BOOST_REQUIRE_EQUAL( result.size(), 3 );
  BOOST_CHECK_EQUAL( result.at(1), 0 );
  BOOST_CHECK_EQUAL( result.at(2), 3 );
}

BOOST_AUTO_TEST_CASE(FeathersZeroDefined)
{
  Lineside::BOPArrayMASHData mashd;
  mashd.id = 255;

  mashd.settings["Red"] = "0";
  mashd.settings["Green"] = "2";
  mashd.settings["Feather0"] = "1";
  
  std::string msg = "Configuration problem for 00:00:00:ff - Feather '0' defined";
  BOOST_CHECK_EXCEPTION( mashd.ExtractFeathers(),
			 Lineside::BadPWItemDataException,
			 GetExceptionMessageChecker<Lineside::BadPWItemDataException>( msg ) );
}

BOOST_AUTO_TEST_CASE(FeathersNonSequential)
{
  Lineside::BOPArrayMASHData mashd;
  mashd.id = 255;

  mashd.settings["Red"] = "2";
  mashd.settings["Green"] = "1";
  mashd.settings["Feather2"] = "0";

  std::string msg = "Configuration problem for 00:00:00:ff - Feathers are not sequential from one";
  BOOST_CHECK_EXCEPTION( mashd.ExtractFeathers(),
			 Lineside::BadPWItemDataException,
			 GetExceptionMessageChecker<Lineside::BadPWItemDataException>( msg ) );
}

BOOST_AUTO_TEST_SUITE_END()

// ---------------

BOOST_AUTO_TEST_SUITE_END()
