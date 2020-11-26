#pragma once

#include <string>

//! A wrapper for <a href="http://abyz.me.uk/rpi/pigpio/pigpiod.html">pigpiod</a>
/*!
  Implements the concepts in Tendril using the <a href="http://abyz.me.uk/rpi/pigpio/pigpiod.html">pigpiod library</a>.
  This takes care of initialising and finalising the library, and has mechanisms in place to ensure that the library is not finalised until all the hardware items (pins etc.) which it has supplied are no longer in use.
 */
namespace PiGPIOdpp {
  //! The concept of parsing
  /*!
    There is no actual templated implementation. Individual
    types must specialise the template for themselves.
  */
  template<typename T>
  T Parse(const std::string& src);
}
