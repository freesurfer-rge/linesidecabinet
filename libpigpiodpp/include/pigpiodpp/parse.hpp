#pragma once

#include <string>

namespace PiGPIOdpp {
  //! The concept of parsing
  /*!
    There is no actual templated implementation. Individual
    types must specialise the template for themselves.
  */
  template<typename T>
  T Parse(const std::string& src);
}
