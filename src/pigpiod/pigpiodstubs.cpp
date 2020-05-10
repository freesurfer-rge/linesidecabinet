#include <iostream>
#include <stdexcept>

#include "pigpiod/pigpiodstubs.hpp"

const int piId = 0;

static bool libraryInitialised = false;

int pigpio_start(char *addrStr, char *portStr) {
  std::cout << __FUNCTION__;
  std::cout << ": " << addrStr;
  std::cout << " " << portStr;
  std::cout << std::endl;

  if( libraryInitialised ) {
    throw std::logic_error("Library already initialised");
  }
  
  libraryInitialised = true;
  
  return piId;
}

void pigpio_stop(int pi) {
  std::cout << __FUNCTION__ << std::endl;
  if( piId != pi ) {
    throw std::logic_error("Bad pi");
  }
  libraryInitialised = false;
}
