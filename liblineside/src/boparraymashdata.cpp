#include "lineside/boparraymashdata.hpp"

namespace Lineside {
  BOPArrayMASHData::BOPArrayMASHData()
    : PWItemData(),
      bopArrayRequest(),
      settings() {}
  
  std::map<SignalAspect,unsigned int>
  BOPArrayMASHData::ExtractAspects() const {
    throw std::logic_error(__PRETTY_FUNCTION__);
  }

  std::vector<unsigned int>
  BOPArrayMASHData::ExtractFeathers() const {
    throw std::logic_error(__PRETTY_FUNCTION__);
  }

  
  std::shared_ptr<PWItemModel> BOPArrayMASHData::Construct(Tendril::HardwareManager& hw,
							   SoftwareManager& sw ) const {
    // Work around unused parameter warning
    this->UnusedSoftwareManager(sw);
    
    hw.bopArrayProviderRegistrar.Retrieve("GPIO");
    throw std::logic_error(__PRETTY_FUNCTION__);
  }
}
