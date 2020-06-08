/*! \file utility.hpp
  \brief Header file for utility bits and pieces
*/

#pragma once

#include "linesideexceptions.hpp"

//! Macro for locking a weak_ptr
/*!
  This locks the weak_ptr \a WP and assigns it to the shared_ptr \a SP. If
  the \c lock() call fails, a Lineside::PointerLockFailureException is thrown
  which contains details about the failure location.
 */
#define LOCK_OR_THROW(SP, WP) auto SP = WP.lock(); \
  if( !SP ) {								\
    throw Lineside::PointerLockFailureException(__FILE__, __LINE__);	\
  }
