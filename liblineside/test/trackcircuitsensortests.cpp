#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include <sstream>

#include "lineside/trackcircuitsensor.hpp"

char const* sensorNames[] = { "Steady", "Flashing" };
Lineside::TrackCircuitSensor sensors[] = {
  Lineside::TrackCircuitSensor::OccupiedIsLow,
  Lineside::TrackCircuitSensor::OccupiedIsHigh
};

auto nameToSensorZip = boost::unit_test::data::make(sensorNames)
  ^ boost::unit_test::data::make(sensors);

BOOST_AUTO_TEST_SUITE( TrackCircuitSensor )

BOOST_DATA_TEST_CASE( ToString, nameToSensorZip, name, sensor )
{
  BOOST_CHECK_EQUAL( name, Lineside::ToString(sensor) );
}

BOOST_DATA_TEST_CASE( StreamInsertion, nameToSensorZip, name, sensor )
{
  std::stringstream res;
  res << sensor;
  BOOST_CHECK_EQUAL( res.str(), name );
}

BOOST_DATA_TEST_CASE( Parse, nameToSensorZip, name, sensor )
{
  BOOST_CHECK_EQUAL( sensor, Lineside::Parse<Lineside::TrackCircuitSensor>(name) );
}

BOOST_AUTO_TEST_SUITE_END()
