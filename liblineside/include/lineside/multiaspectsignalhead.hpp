#pragma once

#include "lineside/signalstate.hpp"
#include "lineside/signalaspect.hpp"
#include "lineside/signalflash.hpp"

#include "lineside/pwitemmodel.hpp"

namespace Lineside {
  //! Concept of a multiple aspect signal head
  class MultiAspectSignalHead : public PWItemModel {
  public:
    MultiAspectSignalHead(const ItemId id) :
      PWItemModel(id) {}
    
    virtual void SetState(const SignalState wantedState,
			  const SignalFlash wantedFlash,
			  const unsigned int wantedFeather) = 0;
  };
}
