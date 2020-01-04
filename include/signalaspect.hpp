#pragma once

#include <iostream>
#include <string>

namespace Lineside {
  enum class SignalAspect { Red,
			    DoubleYellow,
			    Yellow,
			    Green
  };

  std::ostream& operator<<( std::ostream& os, const SignalAspect s );
  
  std::string ToString( const SignalAspect s );
}
