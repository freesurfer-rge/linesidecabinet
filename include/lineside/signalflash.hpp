#pragma once

#include <iostream>
#include <string>

#include "parse.hpp"

namespace Lineside {
  enum class SignalFlash { Steady, Flashing };

  std::ostream& operator<<( std::ostream& os, const SignalFlash s );
  
  std::string ToString( const SignalFlash s );

  //! Template specialisation to parse a string to a SignalFlash
  template<>
  SignalFlash Parse<SignalFlash>(const std::string& src);
}
