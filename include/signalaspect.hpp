#pragma once

#include <iostream>
#include <string>

namespace Lineside {
  enum class SignalAspect { Red,
			    Yellow1,
			    Yellow2,
			    Green
  };

  std::ostream& operator<<( std::ostream& os, const SignalAspect s );
  
  std::string ToString( const SignalAspect s );
}
