#pragma once

#ifdef HAVE_PIGPIO
#include <pigpiod_if2.h>
#else
#include "pigpiod/pigpiodstubs.hpp"
#endif

#include "parse.hpp"

namespace Lineside {
  namespace PiGPIOd {
    //! Enumeration of possibilities for the pullup/pulldown resistor on an input pin
    enum class GPIOPull {
			 Off = PI_PUD_OFF,
			 Down = PI_PUD_DOWN,
			 Up = PI_PUD_UP
    };

    std::ostream& operator<<( std::ostream& os, const GPIOPull p );
  
    std::string ToString( const GPIOPull p );
  }
  
  //! Template specialisation to parse a string to a GPIOPull
  template<>
  PiGPIOd::GPIOPull Parse<PiGPIOd::GPIOPull>(const std::string& src);
}
