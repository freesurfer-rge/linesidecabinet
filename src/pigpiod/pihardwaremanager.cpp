#include "pigpiod/pihardwaremanager.hpp"


namespace Lineside {
  namespace PiGPIOd {
    PiHardwareManager::PiHardwareManager(const HardwareManagerData& data) :
      piManager(PiManager::CreatePiManager()),
      gpioProvider(),
      gpOutputProvider() {
      if( data.settings.size() != 0 ) {
	throw std::logic_error("Settings not supported for PiHardwareManager");
      }
    }
  }
}
