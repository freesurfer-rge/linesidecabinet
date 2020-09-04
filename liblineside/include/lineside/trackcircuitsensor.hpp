#pragma once

#include <iostream>
#include <string>

#include "lineside/parse.hpp"

namespace Lineside {
  enum class TrackCircuitSensor { OccupiedIsLow, OccupiedIsHigh };

  std::ostream& operator<<( std::ostream& os, const TrackCircuitSensor s );
  
  std::string ToString( const TrackCircuitSensor s );

  //! Template specialisation to parse a string to a TrackCircuitSensor
  template<>
  TrackCircuitSensor Parse<TrackCircuitSensor>(const std::string& src);
}
