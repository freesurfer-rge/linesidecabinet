#include <map>

#include "tendril/devices/directdrivesn74x595.hpp"
#include "tendril/devices/boparray595.hpp"

namespace Tendril::Devices {
  BOPArray595::BOPArray595(std::shared_ptr<DirectDriveSN74x595> controller,
			   std::vector<unsigned int> pins)
    : BOPArray(pins.size()),
      controller(controller),
      pinMapping(pins) {}

  void BOPArray595::Update() {
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
