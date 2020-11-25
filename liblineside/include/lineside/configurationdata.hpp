#pragma once

#include <vector>
#include <memory>

#include "tendril/hardwaremanagerdata.hpp"

#include "lineside/softwaremanagerdata.hpp"
#include "lineside/pwitemdata.hpp"

namespace Lineside {
  //! Class to hold all configuration data
  class ConfigurationData {
  public:
    ConfigurationData() :
      swManager(),
      hwManager(),
      pwItems() {}
    
    SoftwareManagerData swManager;

    Tendril::HardwareManagerData hwManager;

    std::vector<std::shared_ptr<PWItemData>> pwItems;
  };
}
