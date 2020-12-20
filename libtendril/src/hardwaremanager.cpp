#include "tendril/hardwaremanager.hpp"

namespace Tendril {
  std::unique_ptr<I2CCommunicator>
  HardwareManager::GetI2CComms(const HardwareRequestData& hrd) {
    auto provider = this->i2cCommProviderRegistrar.Retrieve(hrd.providerName);

    return provider->GetHardware(hrd.idOnProvider, hrd.settings);
  }
}
