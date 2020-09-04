#include <stdexcept>
#include <boost/bimap.hpp>

#include "lineside/trackcircuitsensor.hpp"

namespace Lineside {
  static boost::bimap<TrackCircuitSensor,std::string> convertor;

  static void initconvertor() {
    typedef decltype(convertor)::value_type pos;
    convertor.insert( pos(TrackCircuitSensor::OccupiedIsLow, "OccupiedIsLow") );
    convertor.insert( pos(TrackCircuitSensor::OccupiedIsHigh, "OccupiedIsHigh") );
  }
  
  std::ostream& operator<<( std::ostream& os, const TrackCircuitSensor s ) {
    os << ToString( s );
    
    return os;
  }

  std::string ToString( const TrackCircuitSensor s ) {
    if( convertor.empty() ) {
      initconvertor();
    }

    std::string res;
    try {
      res = convertor.left.at(s);
    }
    catch( std::out_of_range& e ) {
      std::stringstream msg;
      msg << "Unrecognised TrackCircuitSensor: ";
      msg << static_cast<int>(s);
      throw std::runtime_error(msg.str());
    }

    return res;
  }
  
  template<>
  TrackCircuitSensor Parse<TrackCircuitSensor>(const std::string& src) {
    if( convertor.empty() ) {
      initconvertor();
    }

    try {
      TrackCircuitSensor sf;
      sf = convertor.right.at(src);
      return sf;
    }
    catch( std::out_of_range& e ) {
      std::stringstream msg;
      msg << "Could not parse '";
      msg << src;
      msg << "' to TrackCircuitSensor";
      throw std::invalid_argument(msg.str());
    }
  }
}
