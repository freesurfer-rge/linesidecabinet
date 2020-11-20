#pragma once

#include <mutex>
#include <map>
#include <chrono>
#include <string>

#include "tendril/binaryoutputpin.hpp"

#include "lineside/multiaspectsignalhead.hpp"


namespace Lineside {
  class DirectDriveMASHData;

  //! Implementation of a multiple aspect signal head where each pin is directly controlled
  class DirectDriveMASH : public MultiAspectSignalHead {
  public:
    const std::chrono::milliseconds FlashInterval = std::chrono::milliseconds(500);

    virtual void OnActivate() override;

    virtual void OnDeactivate() override;

    virtual std::chrono::milliseconds OnRun() override;

    virtual bool HaveStateChange() override;

    //! Set the desired state of the signal head
    virtual void SetState(const SignalState wantedState,
		  const SignalFlash wantedFlash,
		  const unsigned int wantedFeather) override;

  private:
    friend class DirectDriveMASHData;

    std::mutex stateChangeMtx;
    
    SignalState currentState;
    SignalState desiredState;
    SignalFlash currentFlash;
    SignalFlash desiredFlash;
    unsigned int currentFeather;
    unsigned int desiredFeather;

    bool lastFlashStatus;
    
    std::unique_ptr<Tendril::BinaryOutputPin> red;
    std::unique_ptr<Tendril::BinaryOutputPin> yellow1;
    std::unique_ptr<Tendril::BinaryOutputPin> yellow2;
    std::unique_ptr<Tendril::BinaryOutputPin> green;
    
    std::vector<std::unique_ptr<Tendril::BinaryOutputPin>> feathers;

    DirectDriveMASH(const ItemId signalHeadId) :
      MultiAspectSignalHead(signalHeadId),
      stateChangeMtx(),
      currentState(SignalState::Red),
      desiredState(SignalState::Red),
      currentFlash(SignalFlash::Steady),
      desiredFlash(SignalFlash::Steady),
      currentFeather(0),
      desiredFeather(0),
      lastFlashStatus(true),
      red(),
      yellow1(),
      yellow2(),
      green(),
      feathers() {}

    std::string buildStateString(const SignalState state,
				 const SignalFlash flash,
				 const unsigned int feather) const;
    
    void turnAllOff();

    void setStateFromDesired();

    void setFeatherFromDesired();
  };
}
