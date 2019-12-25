#include <thread>

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
    std::lock_guard<std::mutex> lockState(this->stateChangeMtx);
    
    LOCK_OR_THROW( servoCtrl, this->servo );
    if( this->HaveStateChange() ) {
      int startPWM;
      int stopPWM;
      if( this->desiredState == TurnoutState::Curved ) {
	startPWM = this->pwmStraight;
	stopPWM = this->pwmCurved;
      } else {
	startPWM = this->pwmCurved;
	stopPWM = this->pwmStraight;
      }
      int pwmStep = (stopPWM-startPWM) / static_cast<int>(this->MoveSteps);

      // Count from 1 since we don't have to move to the starting position
      for( unsigned int i=1; i<this->MoveSteps; i++ ) {
	unsigned int nxt = startPWM + (i*pwmStep);
	servoCtrl->Set(nxt);
	std::this_thread::sleep_for(this->MoveSleep);
      }
      // Make the last step exact
      servoCtrl->Set(stopPWM);
    }
    this->currentState = this->desiredState;
    
    return this->SleepInterval;
  }

  bool ServoTurnoutMotor::HaveStateChange() {
    return this->desiredState != this->currentState;
  }

  void ServoTurnoutMotor::SetState(const TurnoutState desired) {
    std::lock_guard<std::mutex> lockState(this->stateChangeMtx);
    this->desiredState = desired;
    this->WakeController();
  }
}
