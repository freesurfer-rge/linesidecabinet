#pragma once

#include <memory>
#include <vector>

#include "tendril/boparray.hpp"

namespace Tendril::Devices {
  class DirectDriveSN74x164;

  //! A BOPArray controlled by an SN74x164 shift register
  class BOPArray164 : public BOPArray {
  public:
    //! Create an instance
    BOPArray164(std::shared_ptr<DirectDriveSN74x164> controller,
                std::vector<unsigned int> pins);

    virtual void Update() override;
  private:
    std::shared_ptr<DirectDriveSN74x164> controller;
    std::vector<unsigned int> pinMapping;
  };
}
