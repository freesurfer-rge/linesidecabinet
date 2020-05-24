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

#define PI_BAD_GPIO -3

#define RISING_EDGE  0
#define FALLING_EDGE 1
#define EITHER_EDGE  2

typedef enum
{
   pigif_bad_send           = -2000,
   pigif_bad_recv           = -2001,
   pigif_bad_getaddrinfo    = -2002,
   pigif_bad_connect        = -2003,
   pigif_bad_socket         = -2004,
   pigif_bad_noib           = -2005,
   pigif_duplicate_callback = -2006,
   pigif_bad_malloc         = -2007,
   pigif_bad_callback       = -2008,
   pigif_notify_failed      = -2009,
   pigif_callback_not_found = -2010,
   pigif_unconnected_pi     = -2011,
   pigif_too_many_pis       = -2012,
} pigifError_t;


#ifdef __cplusplus
extern "C" {
#endif
  int pigpio_start(char *addrStr, char *portStr);

  void pigpio_stop(int pi);

  // ===================================================
  
  int set_mode(int pi, unsigned gpio, unsigned mode);

  int gpio_read(int pi, unsigned gpio);
  
  int gpio_write(int pi, unsigned gpio, unsigned level);

  typedef void (*CBFunc_t)
  (int pi, unsigned user_gpio, unsigned level, uint32_t tick);

  typedef void (*CBFuncEx_t)
  (int pi, unsigned user_gpio, unsigned level, uint32_t tick, void *userdata);
  
  int callback_ex(int pi, unsigned user_gpio, unsigned edge, CBFuncEx_t f, void *userdata);
  
  int callback_cancel(unsigned callback_id);
  
  // ===================================================
  
  char *pigpio_error(int errnum);
#ifdef __cplusplus
}
#endif
