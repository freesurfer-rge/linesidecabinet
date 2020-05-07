#pragma once

#include <vector>
#include <memory>

#include "softwaremanagerdata.hpp"
#include "hardwaremanagerdata.hpp"
#include "pwitemdata.hpp"

namespace Lineside {
  //! Class to hold all configuration data
  class ConfigurationData {
  public:
    ConfigurationData() :
      swManager(),
      hwManager(),
      pwItems() {}
    
    SoftwareManagerData swManager;

    HardwareManagerData hwManager;

    std::vector<std::shared_ptr<PWItemData>> pwItems;
  };
}
