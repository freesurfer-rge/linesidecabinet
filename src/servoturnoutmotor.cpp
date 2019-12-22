#include "servoturnoutmotor.hpp"

namespace Lineside {
  void ServoTurnoutMotor::OnActivate() {
    auto servoCtrl = this->servo.lock();
    if( servoCtrl.use_count() == 0 ) {
      throw std::logic_error("ServoTurnoutMotor: servo pointer expired");
    }
    servoCtrl->Set(this->pwmStraight);
    this->currentState = TurnoutState::Straight;
    this->lastState = TurnoutState::Straight;
  }

  void ServoTurnoutMotor::OnDeactivate() {}

  std::chrono::milliseconds ServoTurnoutMotor::OnRun() {
    throw std::logic_error(__PRETTY_FUNCTION__);
  }

  bool ServoTurnoutMotor::HaveStateChange() {
    return this->lastState != this->currentState;
  }

  void ServoTurnoutMotor::SetState(const TurnoutState desired) {
    if( desired == this->lastState ) {
      throw std::logic_error(__PRETTY_FUNCTION__);
    }
    throw std::logic_error(__PRETTY_FUNCTION__);
  }
}
