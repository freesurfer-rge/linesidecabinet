#include <stdexcept>

#include "pigpiod/pigpiodstubs.hpp"

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


int gpio_write(int pi, unsigned gpio, unsigned level) {
  (*pigpiodOS) << __FUNCTION__
	       << " " << pi
	       << " " << gpio
	       << " " << level << std::endl;
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

