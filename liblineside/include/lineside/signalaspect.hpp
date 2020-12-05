#pragma once

#include <iostream>
#include <string>

#include "lineside/parse.hpp"

namespace Lineside {
  //! Enumeration of allowed signal aspects
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

  //! Function to try to parse a string to a SignalAspect
  bool TryParse(const std::string& src, SignalAspect& dest);
}
