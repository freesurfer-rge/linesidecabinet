#pragma once

#ifdef HAVE_PIGPIO
#include <pigpiod_if2.h>
#else
#include "pigpiod/pigpiodstubs.hpp"
#endif

namespace Lineside {
  namespace PiGPIOd {
    enum class GPIOMode {
			 Input = PI_INPUT,
			 Output = PI_OUTPUT
    };
  }
}
