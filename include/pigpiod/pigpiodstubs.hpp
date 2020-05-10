/** \file
 * Stubs for use on a machine without PiGPIOd
 */
#pragma once

#include <iostream>

//! Stream to be used for output from the stubs (default std::cout)
extern std::ostream* pigpiodOS;

#ifdef HAVE_PIGPIO
#error "The real pigpiod library is available. Do not use stubs"
#endif

#define PI_INPUT  0
#define PI_OUTPUT 1

#ifdef __cplusplus
extern "C" {
#endif
  int pigpio_start(char *addrStr, char *portStr);

  void pigpio_stop(int pi);

  int set_mode(int pi, unsigned gpio, unsigned mode);

  char *pigpio_error(int errnum);
#ifdef __cplusplus
}
#endif
