#pragma once

#include <iostream>
#include <string>

namespace Lineside {
  enum class SignalFlash { Steady, Flashing };

  std::ostream& operator<<( std::ostream& os, const SignalFlash s );
  
  std::string ToString( const SignalFlash s );
}
