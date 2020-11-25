#include "tendril/devices/pca9685.hpp"

#include "pigpiodpp/pimanager.hpp"
#include "pigpiodpp/pibopprovider.hpp"
#include "pigpiodpp/pibipprovider.hpp"
#include "pigpiodpp/piboparrayprovider.hpp"
#include "pigpiodpp/i2cpi.hpp"

#include "pigpiodpp/pihardwaremanagerfactory.hpp"

namespace PiGPIOdpp {
  std::shared_ptr<Tendril::HardwareManager>
  GetHardwareManager(const std::vector<Tendril::Devices::I2CDeviceData>& i2cDevices) {
    auto result = std::make_shared<Tendril::HardwareManager>();
    auto pimanager = PiManager::CreatePiManager();

    // Set up the GPIO providers
    auto bopProvider = std::make_shared<PiBOPProvider>(pimanager);
    result->bopProviderRegistrar.Register(GPIO, bopProvider );

    auto bipProvider = std::make_shared<PiBIPProvider>(pimanager);
    result->bipProviderRegistrar.Register(GPIO, bipProvider );

    auto bopArrayProvider = std::make_shared<PiBOPArrayProvider>(pimanager);
    result->bopArrayProviderRegistrar.Register(GPIO, bopArrayProvider );
    
    // Setup the I2C devices... may want this in its own class
    for( auto data: i2cDevices ) {
      auto i2cpi = new I2CPi(pimanager, data.bus, data.address);
      auto communicator = std::unique_ptr<Tendril::I2CCommunicator>(i2cpi);
      if( data.kind == "pca9685" ) {
	auto dev = std::make_shared<Tendril::Devices::PCA9685>(data.name,
							       data.settings,
							       communicator);
	dev->Register(*result);
      } else {
	std::stringstream msg;
	msg << "Unrecognised I2C device: " << data.kind;
	throw std::logic_error(msg.str().c_str());
      }
    }
    
    return result;
  }
}
