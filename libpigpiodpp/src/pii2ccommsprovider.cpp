#include "pigpiodpp/pimanager.hpp"
#include "pigpiodpp/i2cpi.hpp"
#include "pigpiodpp/i2cdeviceassignedexception.hpp"

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
    // We expect I2C addresses to be in hex
    unsigned int addr = std::stoul(hardwareId, nullptr, 16);

    if( this->assignedAddresses.count(addr) != 0 ) {
      throw I2CDeviceAssignedException(this->getBusId(), addr);
    }
    this->assignedAddresses.insert(addr);

    std::unique_ptr<Tendril::I2CCommunicator> communicator;
    communicator = std::make_unique<I2CPi>(this->pi, this->getBusId(), addr);

    return communicator;
  }
}
