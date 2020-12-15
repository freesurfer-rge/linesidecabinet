#pragma once

#include <memory>
#include <vector>

#include "tendril/boparray.hpp"

namespace Tendril::Devices {
  class DirectDriveSN74x595;

  //! A BOPArray controlled by an SN74x595 shift register
  class BOPArray595 : public BOPArray {
  public:
    //! Create an instance
    BOPArray595(std::shared_ptr<DirectDriveSN74x595> controller,
		std::vector<unsigned int> pins);

    virtual void Update() override;
  private:
    std::shared_ptr<DirectDriveSN74x595> controller;
    std::vector<unsigned int> pinMapping;
  };
}
