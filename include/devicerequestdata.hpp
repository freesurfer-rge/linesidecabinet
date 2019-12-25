#pragma once

#include <string>
#include <map>

namespace Lineside {
  class DeviceRequestData {
  public:
    DeviceRequestData() :
      controller("unset"),
      controllerData("unset"),
      settings() {}
    
    std::string controller;
    std::string controllerData;
    std::map<std::string,std::string> settings;
  };
}
