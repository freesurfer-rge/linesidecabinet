#include "pigpiodpp/pimanager.hpp"
#include "pigpiodpp/i2cpi.hpp"

#include "pigpiodpp/pii2ccommsprovider.hpp"


namespace PiGPIOdpp {
  int PiI2CCommsProvider::getPi() const {
    return this->pi->getId();
  }

  unsigned int PiI2CCommsProvider::getBusId() const {
    return this->busId;
  }
  
  std::unique_ptr<Tendril::I2CCommunicator>
  PiI2CCommsProvider::GetHardware(const std::string& hardwareId,
				  const Tendril::SettingsMap& settings) {
    if( settings.size() != 0 ) {
      throw std::logic_error("Settings not allowed for I2CCommunicator");
    }
    unsigned int addr = std::stoul(hardwareId);

    std::unique_ptr<Tendril::I2CCommunicator> communicator;
    communicator = std::make_unique<I2CPi>(this->pi, this->getBusId(), addr);

    return communicator;
  }
}
