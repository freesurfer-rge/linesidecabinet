#pragma once

#include "pwitemmodel.hpp"

#include "turnoutstate.hpp"

namespace Lineside {
  class TurnoutMotor : public PWItemModel {
  public:
    virtual void SetState(const TurnoutState desired) = 0;

    virtual TurnoutState getState() const {
      return this->currentState;
    }
    
  protected:
    TurnoutState currentState;
    
    TurnoutMotor(const ItemId turnoutId) :
      PWItemModel(turnoutId),
      currentState(TurnoutState::Straight) {}
  };
}
