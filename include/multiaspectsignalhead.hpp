#pragma once

#include <mutex>
#include <map>
#include <chrono>

#include "signalstate.hpp"
#include "signalaspect.hpp"
#include "signalflash.hpp"

#include "binaryoutputpin.hpp"

#include "pwitemmodel.hpp"

namespace Lineside {
  class MultiAspectSignalHeadData;
  
  class MultiAspectSignalHead : public PWItemModel {
  public:
    const std::chrono::milliseconds FlashInterval = std::chrono::milliseconds(500);

    virtual void OnActivate() override;

    virtual void OnDeactivate() override;

    virtual std::chrono::milliseconds OnRun() override;

    virtual bool HaveStateChange() override;

    void SetState(const SignalState wantedState, const unsigned int wantedFeather);
  private:
    friend class MultiAspectSignalHeadData;

    std::mutex stateChangeMtx;
    
    SignalState currentState;
    SignalState desiredState;
    SignalFlash currentFlash;
    SignalFlash desiredFlash;
    unsigned int currentFeather;
    unsigned int desiredFeather;

    bool lastFlashStatus;
    
    std::weak_ptr<BinaryOutputPin> red;
    std::weak_ptr<BinaryOutputPin> yellow1;
    std::weak_ptr<BinaryOutputPin> yellow2;
    std::weak_ptr<BinaryOutputPin> green;
    
    std::vector<std::weak_ptr<BinaryOutputPin>> feathers;

    MultiAspectSignalHead(const ItemId signalHeadId) :
      PWItemModel(signalHeadId),
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
  };
}
