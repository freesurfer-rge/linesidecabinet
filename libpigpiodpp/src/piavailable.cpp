#include "pigpiodpp/piavailable.hpp"

namespace PiGPIOdpp {
  const bool stubsEnabled =
#ifdef PIGPIODPP_HAVE_PIGPIO
    true
#else
    false
#endif
    ;
}
