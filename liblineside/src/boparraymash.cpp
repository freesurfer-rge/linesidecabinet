#include "lineside/boparraymash.hpp"

namespace Lineside {
  void BOPArrayMASH::OnActivate() {
    this->markAllOff();
    this->pins->Set(this->aspects.at(SignalAspect::Red), true);
    this->pins->Update();
  }

  void BOPArrayMASH::OnDeactivate() {
    this->markAllOff();
    this->pins->Update();
  }

  unsigned int BOPArrayMASH::GetAspectCount() const {
    return this->aspects.size();
  }

  unsigned int BOPArrayMASH::GetFeatherCount() const {
    return this->feathers.size();
  }

  void BOPArrayMASH::markAllOff() {
    const size_t nPins = this->GetAspectCount() + this->GetFeatherCount();
    for( size_t i=0; i<nPins; ++i ) {
      this->pins->Set(i, false);
    }
  }
}
