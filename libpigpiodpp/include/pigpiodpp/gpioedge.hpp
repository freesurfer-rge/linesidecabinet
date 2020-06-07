#pragma once

#ifdef HAVE_PIGPIO
#include <pigpiod_if2.h>
#else
#include "pigpiod/pigpiodstubs.hpp"
#endif

namespace Lineside {
  namespace PiGPIOd {
    enum class GPIOEdge {
			 Rising = RISING_EDGE,
			 Falling = FALLING_EDGE,
			 Either = EITHER_EDGE
    };
  }
}
