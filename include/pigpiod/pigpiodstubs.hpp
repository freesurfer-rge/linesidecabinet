/** \file
 * Stubs for use on a machine without PiGPIOd
 */

#include <iostream>

//! Stream to be used for output from the stubs (default std::cout)
extern std::ostream* pigpiodOS;

#ifdef HAVE_PIGPIO
#error "The real pigpiod library is available. Do not use stubs"
#endif

#ifdef __cplusplus
extern "C" {
#endif

  int pigpio_start(char *addrStr, char *portStr);

  void pigpio_stop(int pi);

#ifdef __cplusplus
}
#endif
