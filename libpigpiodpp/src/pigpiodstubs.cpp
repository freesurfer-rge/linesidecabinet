#include <stdexcept>
#include <boost/predef.h>

#include "pigpiodstubs.hpp"

const int piId = 0;

std::ostream* pigpiodOS = &std::cout;

static bool libraryInitialised = false;

// =============================================================================

int pigpio_start(char *addrStr, char *portStr) {
  (*pigpiodOS) << __FUNCTION__;
  if( addrStr ) {
    (*pigpiodOS) << " " << addrStr;
  }
  if( portStr ) {
    (*pigpiodOS) << " " << portStr;
  }
  (*pigpiodOS) << std::endl;

  if( libraryInitialised ) {
    throw std::logic_error("Library already initialised");
  }
  
  libraryInitialised = true;
  
  return piId;
}

void pigpio_stop(int pi) {
  (*pigpiodOS) << __FUNCTION__ << std::endl;
  if( piId != pi ) {
    throw std::logic_error("Bad pi");
  }
  libraryInitialised = false;
}

// =============================================================================

int set_mode(int pi, unsigned gpio, unsigned mode) {
  (*pigpiodOS) << __FUNCTION__
	       << " " << pi
	       << " " << gpio
	       << " " << mode << std::endl;
  return 0;
}


int gpio_read(int pi, unsigned gpio) {
  (*pigpiodOS) << __FUNCTION__
	       << " " << pi
	       << " " << gpio << std::endl;
  return 0;
}

int gpio_write(int pi, unsigned gpio, unsigned level) {
  (*pigpiodOS) << __FUNCTION__
	       << " " << pi
	       << " " << gpio
	       << " " << level << std::endl;
  return 0;
}

int set_pull_up_down(int pi, unsigned gpio, unsigned pud) {
  (*pigpiodOS) << __FUNCTION__
	       << " " << pi
	       << " " << gpio
	       << " " << pud << std::endl;
  return 0;
}

int set_glitch_filter(int pi, unsigned user_gpio, unsigned steady) {
  (*pigpiodOS) << __FUNCTION__
	       << " " << pi
	       << " " << user_gpio
	       << " " << steady << std::endl;
  return 0;
}

#if defined(BOOST_COMP_GNUC)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#elif defined(BOOST_COMP_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif
int callback_ex(int pi, unsigned user_gpio, unsigned edge, CBFuncEx_t f, void *userdata) {
  (*pigpiodOS) << __FUNCTION__
	       << " " << pi
	       << " " << user_gpio
	       << " " << edge << std::endl;
  return 0;
}
#if defined(BOOST_COMP_GNUC)
#pragma GCC diagnostic pop
#elif defined(BOOST_COMP_CLANG)
#pragma clang diagnostic pop
#endif
  
int callback_cancel(unsigned callback_id) {
   (*pigpiodOS) << __FUNCTION__
		<< " " << callback_id << std::endl;
   return 0;
}

// =============================================================================

char *pigpio_error(int errnum) {
  (*pigpiodOS) << __FUNCTION__
	       << " " << errnum << std::endl;
  // Following is ugly but we're short on options given the
  // signature we have to match
  return const_cast<char*>("Sorry no error mappings defined");
}

