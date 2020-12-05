#include <boost/test/unit_test.hpp>

#include "lineside/boparraymashdata.hpp"
#include "lineside/boparraymash.hpp"
#include "lineside/linesideexceptions.hpp"

#include "exceptionmessagecheck.hpp"
#include "mockmanagerfixture.hpp"

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

BOOST_FIXTURE_TEST_SUITE(Construct, MockManagerFixture)

BOOST_AUTO_TEST_CASE(Smoke)
{
  Lineside::BOPArrayMASHData mashd;
  mashd.id = 255;

  mashd.settings["Red"] = "2";
  mashd.settings["Green"] = "1";
  mashd.settings["Feather1"] = "0";

  mashd.bopArrayRequest.controller = "MockBOPArray";
  mashd.bopArrayRequest.settings["0"] = "18";
  mashd.bopArrayRequest.settings["1"] = "19";
  mashd.bopArrayRequest.settings["2"] = "26";

  auto result = mashd.Construct(*(this->hwManager), *(this->swManager));
  BOOST_REQUIRE(result);
  auto bopArrayMash = std::dynamic_pointer_cast<Lineside::BOPArrayMASH>(result);
  BOOST_CHECK( bopArrayMash );
}
  
BOOST_AUTO_TEST_CASE(AspectFeatherBOPArraySizeMismatch)
{
  Lineside::BOPArrayMASHData mashd;
  mashd.id = 255;

  mashd.settings["Red"] = "2";
  mashd.settings["Green"] = "1";
  mashd.settings["Feather1"] = "0";

  mashd.bopArrayRequest.settings["0"] = "18";
  mashd.bopArrayRequest.settings["1"] = "19";

  std::string msg = "Configuration problem for 00:00:00:ff - Number of feathers and aspects does not match BOPArray size";
  BOOST_CHECK_EXCEPTION( mashd.Construct(*(this->hwManager), *(this->swManager)),
			 Lineside::BadPWItemDataException,
			 GetExceptionMessageChecker<Lineside::BadPWItemDataException>(msg) );
}

BOOST_AUTO_TEST_CASE(DuplicatePinRequest)
{
  Lineside::BOPArrayMASHData mashd;
  mashd.id = 255;

  mashd.settings["Red"] = "2";
  mashd.settings["Green"] = "1";
  mashd.settings["Feather1"] = "1";

  mashd.bopArrayRequest.settings["0"] = "18";
  mashd.bopArrayRequest.settings["1"] = "19";
  mashd.bopArrayRequest.settings["2"] = "26";

  std::string msg = "Configuration problem for 00:00:00:ff - At least one pin in BOPArray requested twice";
  BOOST_CHECK_EXCEPTION( mashd.Construct(*(this->hwManager), *(this->swManager)),
			 Lineside::BadPWItemDataException,
			 GetExceptionMessageChecker<Lineside::BadPWItemDataException>(msg) );
}

BOOST_AUTO_TEST_CASE(PinsNotSequential)
{
  Lineside::BOPArrayMASHData mashd;
  mashd.id = 255;

  mashd.settings["Red"] = "2";
  mashd.settings["Green"] = "3";
  mashd.settings["Feather1"] = "0";

  mashd.bopArrayRequest.settings["0"] = "18";
  mashd.bopArrayRequest.settings["1"] = "19";
  mashd.bopArrayRequest.settings["2"] = "26";

  std::string msg = "Configuration problem for 00:00:00:ff - BOPArray pin requests not sequential from zero";
  BOOST_CHECK_EXCEPTION( mashd.Construct(*(this->hwManager), *(this->swManager)),
			 Lineside::BadPWItemDataException,
			 GetExceptionMessageChecker<Lineside::BadPWItemDataException>(msg) );
}

BOOST_AUTO_TEST_SUITE_END()

// ---------------

BOOST_AUTO_TEST_SUITE_END()
