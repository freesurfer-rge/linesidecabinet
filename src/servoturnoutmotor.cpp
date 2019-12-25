#include "utility.hpp"

#include "servoturnoutmotor.hpp"

namespace Lineside {
  void ServoTurnoutMotor::OnActivate() {
    LOCK_OR_THROW( servoCtrl, this->servo );
    servoCtrl->Set(this->pwmStraight);
    this->currentState = TurnoutState::Straight;
    this->desiredState = TurnoutState::Straight;
  }

  void ServoTurnoutMotor::OnDeactivate() {}

  std::chrono::milliseconds ServoTurnoutMotor::OnRun() {
    throw std::logic_error(__PRETTY_FUNCTION__);
  }

  bool ServoTurnoutMotor::HaveStateChange() {
    return this->desiredState != this->currentState;
  }

  void ServoTurnoutMotor::SetState(const TurnoutState desired) {
    this->desiredState = desired;
    this->WakeController();
  }
}
