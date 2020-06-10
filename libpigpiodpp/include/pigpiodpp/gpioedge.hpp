#pragma once

namespace PiGPIOdpp {
  //! Enumeration of edges for input pin level changes
  enum class GPIOEdge {
		       Rising = 0,
		       Falling = 1,
		       Either = 2
  };
}
