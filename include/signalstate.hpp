#pragma once

#include <iostream>
#include <string>

#include "parse.hpp"

namespace Lineside {
  enum class SignalState { Red,
			   DoubleYellow,
			   Yellow,
			   Green
  };

  std::ostream& operator<<( std::ostream& os, const SignalState s );
  
  std::string ToString( const SignalState s );

  //! Template specialisation to parse a string to a SignalState
  template<>
  SignalState Parse<SignalState>(const std::string& src );
}
