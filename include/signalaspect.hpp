#pragma once

#include <iostream>
#include <string>

#include "parse.hpp"

namespace Lineside {
  enum class SignalAspect { Red,
			    Yellow1,
			    Yellow2,
			    Green
  };

  std::ostream& operator<<( std::ostream& os, const SignalAspect s );
  
  std::string ToString( const SignalAspect s );

  //! Template specialisation to parse a string to a SignalAspect
  template<>
  SignalAspect Parse<SignalAspect>(const std::string& src );
}
