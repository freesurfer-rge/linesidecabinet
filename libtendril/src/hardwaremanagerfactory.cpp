#include "tendril/hardwaremanagerfactory.hpp"

namespace Tendril {
  std::map<std::string,HardwareManagerFactory*> HardwareManagerFactory::factories;

  void HardwareManagerFactory::AddFactory(const std::string name,
					  HardwareManagerFactory* factory) {
    HardwareManagerFactory::factories[name] = factory;
  }
}
