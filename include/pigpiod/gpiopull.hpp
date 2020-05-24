#pragma once

#ifdef HAVE_PIGPIO
#include <pigpiod_if2.h>
#else
#include "pigpiod/pigpiodstubs.hpp"
#endif

namespace Lineside {
  namespace PiGPIOd {
    enum class GPIOPull {
			 Off = PI_PUD_OFF,
			 Down = PI_PUD_DOWN,
			 UP = PI_PUD_UP
    };
  }
}
