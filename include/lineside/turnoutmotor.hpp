#pragma once

#include "lineside/pwitemmodel.hpp"

#include "lineside/turnoutstate.hpp"

namespace Lineside {
  class TurnoutMotor : public PWItemModel {
  public:
    virtual void SetState(const TurnoutState desired) = 0;

    virtual TurnoutState GetState() const {
      return this->currentState;
    }
    
  protected:
    TurnoutState currentState;
    
    TurnoutMotor(const ItemId turnoutId) :
      PWItemModel(turnoutId),
      currentState(TurnoutState::Straight) {}
  };
}
