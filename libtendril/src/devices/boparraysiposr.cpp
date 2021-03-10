#include <map>

#include "tendril/devices/directdrivesiposhiftregister.hpp"
#include "tendril/devices/boparraysiposr.hpp"

namespace Tendril::Devices {
  BOPArraySIPOSR::BOPArraySIPOSR(std::shared_ptr<DirectDriveSIPOShiftRegister> controller,
				 std::vector<unsigned int> pins)
    : BOPArray(pins.size()),
      controller(controller),
      pinMapping(pins) {}

  void BOPArraySIPOSR::Update() {
    std::map<unsigned int, bool> updates;
    
    // Build up list of pins to update on the chip
    for( size_t i=0; i<this->pinState.size(); ++i ) {
      unsigned int pinOnChip = this->pinMapping.at(i);
      bool desiredState = this->pinState.at(i);
      updates[pinOnChip] = desiredState;
    }
    
    //! Send the request
    this->controller->SetPinsAndSend(updates);
  }
}
