#pragma once

#include <iostream>
#include <string>

#include "lineside/parse.hpp"

namespace Lineside {
  //! Enumeration to describe possible states of turnouts
  enum class TurnoutState { Straight,
			    Curved
  };

  std::ostream& operator<<(std::ostream& os, const TurnoutState s);

  std::string ToString( const TurnoutState s );

  //! Template specialisation to parse a string to a TurnoutState
  template<>
  TurnoutState Parse<TurnoutState>(const std::string& src );
}
