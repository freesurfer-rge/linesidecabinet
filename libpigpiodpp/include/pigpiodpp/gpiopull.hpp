#pragma once

#include "pigpiodpp/parse.hpp"

namespace PiGPIOdpp {
  //! Enumeration of possibilities for the pullup/pulldown resistor on an input pin
  enum class GPIOPull {
		       Off = 0,
		       Down = 1,
		       Up = 2
  };
  
  std::ostream& operator<<( std::ostream& os, const GPIOPull p );
  
  std::string ToString( const GPIOPull p );

  //! Template specialisation to parse a string to a GPIOPull
  template<>
  GPIOPull Parse<GPIOPull>(const std::string& src);
}
