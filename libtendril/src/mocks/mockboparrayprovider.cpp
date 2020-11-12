#include "tendril/keyexception.hpp"

#include "tendril/mocks/mockboparrayprovider.hpp"

namespace Tendril::Mocks {
  std::unique_ptr<BOPArray>
  MockBOPArrayProvider::GetHardware(const std::string& hardwareId,
				    const SettingsMap& settings) {
    if( this->hardware.count(hardwareId) != 0 ) {
      throw DuplicateKeyException(hardwareId);
    }

    auto pinList = BOPArray::ExtractPinList(settings);

    auto result = std::make_unique<MockBOPArray>(pinList.size());
    result->settings = settings;
    this->hardware[hardwareId] = result.get();

    return result;
  }
}
