#pragma once

#include <vector>
#include <memory>

#include "lineside/softwaremanagerdata.hpp"
#include "lineside/hardwaremanagerdata.hpp"
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

    HardwareManagerData hwManager;

    std::vector<std::shared_ptr<PWItemData>> pwItems;
  };
}
