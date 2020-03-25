#pragma once

#include <iostream>
#include <string>

namespace Lineside {
  //! The concept of parsing
  /*!
    There is no actual templated implementation. Individual
    types must specialise the template for themselves.
   */
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
