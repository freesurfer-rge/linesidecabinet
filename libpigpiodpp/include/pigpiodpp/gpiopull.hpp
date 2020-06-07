#pragma once

#ifdef HAVE_PIGPIO
#include <pigpiod_if2.h>
#else
#include "pigpiodstubs.hpp"
#endif

#include "pigpiodpp/parse.hpp"

namespace PiGPIOdpp {
  //! Enumeration of possibilities for the pullup/pulldown resistor on an input pin
  enum class GPIOPull {
		       Off = PI_PUD_OFF,
		       Down = PI_PUD_DOWN,
		       Up = PI_PUD_UP
  };
  
  std::ostream& operator<<( std::ostream& os, const GPIOPull p );
  
  std::string ToString( const GPIOPull p );

  //! Template specialisation to parse a string to a GPIOPull
  template<>
  GPIOPull Parse<GPIOPull>(const std::string& src);
}
