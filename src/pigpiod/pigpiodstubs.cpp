#include <iostream>
#include <stdexcept>

#include "pigpiod/pigpiodstubs.hpp"

const int piId = 0;

static std::ostream* os = &std::cout;

static bool libraryInitialised = false;

int pigpio_start(char *addrStr, char *portStr) {
  (*os) << __FUNCTION__;
  if( addrStr ) {
    (*os) << " " << addrStr;
  }
  if( portStr ) {
    (*os) << " " << portStr;
  }
  (*os) << std::endl;

  if( libraryInitialised ) {
    throw std::logic_error("Library already initialised");
  }
  
  libraryInitialised = true;
  
  return piId;
}

void pigpio_stop(int pi) {
  (*os) << __FUNCTION__ << std::endl;
  if( piId != pi ) {
    throw std::logic_error("Bad pi");
  }
  libraryInitialised = false;
}
