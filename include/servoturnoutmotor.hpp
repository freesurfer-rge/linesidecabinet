#pragma once

#include "turnoutmotor.hpp"
#include "pwmchannel.hpp"

namespace Lineside {
  class ServoTurnoutMotorData;
  
  class ServoTurnoutMotor : public TurnoutMotor {
  public:
    const std::chrono::milliseconds SleepInterval = std::chrono::milliseconds(2000);
    const std::chrono::milliseconds MoveSleep = std::chrono::milliseconds(50);
    const unsigned int MoveSteps = 10;
    
    virtual void OnActivate() override;

    virtual void OnDeactivate() override;

    virtual std::chrono::milliseconds OnRun() override;

    virtual bool HaveStateChange() override;

    virtual void SetState(const TurnoutState desired) override;
  private:
    friend class ServoTurnoutMotorData;

    unsigned int pwmStraight;
    unsigned int pwmCurved;
    TurnoutState desiredState;
    std::weak_ptr<PWMChannel> servo;

    ServoTurnoutMotor(const ItemId turnoutId) :
      TurnoutMotor(turnoutId),
      pwmStraight(),
      pwmCurved(),
      desiredState(TurnoutState::Straight),
      servo() {}
  };
}
