#pragma once

#include <map>
#include <string>
#include <memory>

#include "hardwaremanager.hpp"

namespace Tendril {
  class HardwareManagerFactory {
  public:
    static HardwareManagerFactory* GetFactory();

    virtual std::shared_ptr<HardwareManager> GetHardwareManager() = 0;

    virtual ~HardwareManagerFactory() {}

  protected:
    void AddFactory(const std::string name, HardwareManagerFactory* factory);
    
  private:
    static std::map<std::string,HardwareManagerFactory*> factories;
  };
}
