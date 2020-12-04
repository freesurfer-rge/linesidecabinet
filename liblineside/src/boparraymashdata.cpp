#include "lineside/boparraymashdata.hpp"

namespace Lineside {
  BOPArrayMASHData::BOPArrayMASHData()
    : PWItemData(),
      bopArrayRequest(),
      aspectRequests(),
      featherRequests() {}

  void BOPArrayMASHData::CheckData() const {
    throw std::logic_error(__PRETTY_FUNCTION__);
  }

  std::shared_ptr<PWItemModel> BOPArrayMASHData::Construct(Tendril::HardwareManager& hw,
							   SoftwareManager& sw ) const {
    // Work around unused parameter warning
    this->UnusedSoftwareManager(sw);
    
    this->CheckData();
    hw.bopArrayProviderRegistrar.Retrieve("GPIO");
    throw std::logic_error(__PRETTY_FUNCTION__);
  }
}
