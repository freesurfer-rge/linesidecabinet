#pragma once

#ifdef HAVE_PIGPIO
#include <pigpiod_if2.h>
#else
#include "pigpiodpp/pigpiodstubs.hpp"
#endif

namespace PiGPIOdpp {
  //! Enumeration of GPIO modes (input or output)
  enum class GPIOMode {
		       Input = PI_INPUT,
		       Output = PI_OUTPUT
  };
}
