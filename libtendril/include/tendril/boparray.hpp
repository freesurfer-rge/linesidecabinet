#pragma once

#include <vector>
#include "tendril/tendriltypes.hpp"

namespace Tendril {
  //! Abstraction for a collection of binary output pins which are updated together
  class BOPArray {
  public:
    BOPArray(const size_t nPins)
      : pinState(nPins) {}

    virtual ~BOPArray() {}
    
    void Set(const size_t i, const bool level);

    virtual void Update() = 0;

    //! Extract a list of pin ids from the SettingsMap
    static std::vector<std::string> ExtractPinList(const SettingsMap& settings);
  protected:
    std::vector<bool> pinState;
  };
}
