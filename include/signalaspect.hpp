#pragma once

#include <iostream>
#include <string>
#include <type_traits>

namespace Lineside {
  template<typename T>
  T Parse(const std::string& src);
  
  enum class SignalAspect { Red,
			    Yellow1,
			    Yellow2,
			    Green
  };

  std::ostream& operator<<( std::ostream& os, const SignalAspect s );
  
  std::string ToString( const SignalAspect s );

  template<>
  SignalAspect Parse<SignalAspect>(const std::string& src );
}
