#pragma once

#include <string>

//! Namespace for the C++ wrapper of PiGPIOd
namespace PiGPIOdpp {
  //! The concept of parsing
  /*!
    There is no actual templated implementation. Individual
    types must specialise the template for themselves.
  */
  template<typename T>
  T Parse(const std::string& src);
}
