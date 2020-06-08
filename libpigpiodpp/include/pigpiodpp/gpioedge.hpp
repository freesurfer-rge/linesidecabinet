#pragma once

#ifdef PIGPIODPP_HAVE_PIGPIO
#include <pigpiod_if2.h>
#else
#include "pigpiodpp/pigpiodstubs.hpp"
#endif

namespace PiGPIOdpp {
  //! Enumeration of edges for input pin level changes
  enum class GPIOEdge {
		       Rising = RISING_EDGE,
		       Falling = FALLING_EDGE,
		       Either = EITHER_EDGE
  };
}
