#pragma once

#include <memory>
#include <vector>

#include "tendril/boparray.hpp"

namespace Tendril::Devices {
  class DirectDriveSIPOShiftRegister;

  //! A BOPArray controlled by a SIPO shift register
  class BOPArraySIPOSR : public BOPArray {
  public:
    //! Create an instance
    BOPArraySIPOSR(std::shared_ptr<DirectDriveSIPOShiftRegister> controller,
		   std::vector<unsigned int> pins);

    virtual void Update() override;
  private:
    std::shared_ptr<DirectDriveSIPOShiftRegister> controller;
    std::vector<unsigned int> pinMapping;
  };
}
