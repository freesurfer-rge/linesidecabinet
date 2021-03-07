#include <map>
#include <iostream>

#include "tendril/devices/directdrivesn74x164.hpp"
#include "tendril/devices/boparray164.hpp"

namespace Tendril::Devices {
  BOPArray164::BOPArray164(std::shared_ptr<DirectDriveSN74x164> controller,
			   std::vector<unsigned int> pins)
    : BOPArray(pins.size()),
      controller(controller),
      pinMapping(pins) {}

  void BOPArray164::Update() {
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
