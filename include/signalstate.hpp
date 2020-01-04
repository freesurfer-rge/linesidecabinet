#pragma once

#include <iostream>
#include <string>

namespace Lineside {
  enum class SignalState { Red,
			   DoubleYellow,
			   Yellow,
			   Green
  };

  std::ostream& operator<<( std::ostream& os, const SignalState s );
  
  std::string ToString( const SignalState s );
}
