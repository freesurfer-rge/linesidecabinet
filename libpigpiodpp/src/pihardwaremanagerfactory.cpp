#include <iostream>

#include "tendril/devices/pca9685.hpp"

#include "pigpiodpp/pimanager.hpp"
#include "pigpiodpp/pii2ccommsprovider.hpp"
#include "pigpiodpp/pibopprovider.hpp"
#include "pigpiodpp/pibipprovider.hpp"
#include "pigpiodpp/piboparrayprovider.hpp"
#include "pigpiodpp/i2cpi.hpp"

#include "pigpiodpp/pihardwaremanagerfactory.hpp"

namespace PiGPIOdpp {
  std::shared_ptr<Tendril::HardwareManager>
  GetHardwareManager(const Tendril::HardwareManagerData& hwData) {
    if( hwData.settings.size() != 0 ) {
      std::cerr << __FUNCTION__
		<< ": Received settings where none expected"
		<< std::endl;
      throw std::logic_error("Settings not supported for Pi HardwareMananger");
    }
    
    auto result = std::make_shared<Tendril::HardwareManager>();
    auto pimanager = PiManager::CreatePiManager();

    // Set up the I2CComms provider
    const unsigned int i2cBusCount = 2;
    for( unsigned int iBus=0; iBus<i2cBusCount; ++iBus ) {
      auto i2ccommsProvider = std::make_shared<PiI2CCommsProvider>(pimanager, iBus);
      result->i2cCommProviderRegistrar.Register(std::to_string(iBus), i2ccommsProvider);
    }
    
    // Set up the GPIO providers
    auto bopProvider = std::make_shared<PiBOPProvider>(pimanager);
    result->bopProviderRegistrar.Register(GPIO, bopProvider );

    auto bipProvider = std::make_shared<PiBIPProvider>(pimanager);
    result->bipProviderRegistrar.Register(GPIO, bipProvider );

    auto bopArrayProvider = std::make_shared<PiBOPArrayProvider>(pimanager);
    result->bopArrayProviderRegistrar.Register(GPIO, bopArrayProvider );
    
    // Setup the devices
    for( auto data: hwData.devices ) {
      data->ConstructAndRegister(*result);
    }
    
    return result;
  }
}
