#pragma once

#include <memory>
#include <vector>

#include "tendril/boparray.hpp"

#include "pigpiodpp/gpiopin.hpp"

namespace PiGPIOdpp {
  class PiManager;
  
  //! Implementation of a BOPArray for pigpiod
  class PiBOPArray : public Tendril::BOPArray {
  public:
    PiBOPArray(const std::shared_ptr<PiManager> owner,
	       const std::vector<unsigned int>& pinIds);
    
    ~PiBOPArray() {}

    int getPi() const;

    virtual void Update() override;
  private:
    std::shared_ptr<PiManager> pi;
    std::vector<std::unique_ptr<GPIOPin>> pins;
  };
}
