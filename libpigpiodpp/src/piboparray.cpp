#include "pigpiodpp/pimanager.hpp"

#include "pigpiodpp/piboparray.hpp"

namespace PiGPIOdpp {
  PiBOPArray::PiBOPArray(const std::shared_ptr<PiManager> owner,
			 const std::vector<unsigned int>& pinIds)
    : BOPArray(pinIds.size()),
      pi(owner),
      pins() {
    for( auto id : pinIds ) {
      auto nxtPin = this->pi->GetGPIOPin(id);
      nxtPin->SetMode(GPIOMode::Output);
      this->pins.push_back( std::move(nxtPin) );
    }
    this->Update();
  }
  
  int PiBOPArray::getPi() const {
    return this->pi->getId();
  }

  void PiBOPArray::Update() {
    if( this->pins.size() != this->pinState.size() ) {
      throw std::logic_error(__FUNCTION__);
    }
    
    for( size_t i=0; i<this->pins.size(); ++i ) {
      this->pins.at(i)->Set(this->pinState.at(i));
    }
  }
}
