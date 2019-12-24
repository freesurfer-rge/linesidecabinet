#pragma once

#include "linesideexceptions.hpp"

#define LOCK_OR_THROW(SP, WP) auto SP = WP.lock(); \
  if( !SP ) {								\
    throw Lineside::PointerLockFailureException(__FILE__, __LINE__);	\
  }
