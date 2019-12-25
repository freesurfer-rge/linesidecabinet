#pragma once

namespace Lineside {
  enum class TurnoutState { Straight,
			    Curved
  };

  std::ostream& operator<<(std::ostream& os, const TurnoutState s);

  std::string ToString( const TurnoutState s );
}
