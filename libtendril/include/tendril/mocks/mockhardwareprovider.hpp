#pragma once

#include <map>
#include <type_traits>

#include "tendril/keyexception.hpp"
#include "tendril/hardwareprovider.hpp"

namespace Tendril::Mocks {
  template<typename T, typename U>
  class MockHardwareProvider : public HardwareProvider<T> {
  public:
    virtual std::unique_ptr<T>
    GetHardware(const std::string& hardwareId,
		const SettingsMap& settings) override {
      static_assert(std::is_base_of<T, U>::value);
      if( this->hardware.count(hardwareId) != 0 ) {
	throw DuplicateKeyException(hardwareId);
      }

      auto result = std::make_unique<U>();
      result->settings = settings;
      this->hardware[hardwareId] = result.get();

      return result;
    }
    
    //! Allows (dangerous) access to returned resources
    std::map<std::string,U*> hardware;
  };
}
