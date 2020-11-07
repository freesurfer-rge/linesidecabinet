#pragma once

#include <vector>

namespace Tendril {
  //! Abstraction for a collection of binary output pins which are updated together
  class BOPArray {
  public:
    BOPArray(const size_t nPins)
      : pinState(nPins) {}

    virtual ~BOPArray() {}
    
    void Set(const size_t i, const bool level);

    virtual void Update() = 0;
    
  protected:
    std::vector<bool> pinState;
  };
}
