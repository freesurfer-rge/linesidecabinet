#pragma once

#include <map>

#include "tendril/binaryoutputpin.hpp"

#include "lineside/multiaspectsignalhead.hpp"


namespace Lineside {
  class DirectDriveMASHData;

  //! Implementation of a multiple aspect signal head where each pin is directly controlled
  class DirectDriveMASH : public MultiAspectSignalHead {
  public:
    DirectDriveMASH(const ItemId signalHeadId) :
      MultiAspectSignalHead(signalHeadId),
      red(),
      yellow1(),
      yellow2(),
      green(),
      feathers() {}
    
    virtual void OnActivate() override;

    virtual void OnDeactivate() override;

    virtual std::chrono::milliseconds OnRun() override;

    virtual unsigned int GetAspectCount() const override;

    virtual unsigned int GetFeatherCount() const override;
  private:
    friend class DirectDriveMASHData;
    
    std::unique_ptr<Tendril::BinaryOutputPin> red;
    std::unique_ptr<Tendril::BinaryOutputPin> yellow1;
    std::unique_ptr<Tendril::BinaryOutputPin> yellow2;
    std::unique_ptr<Tendril::BinaryOutputPin> green;
    
    std::vector<std::unique_ptr<Tendril::BinaryOutputPin>> feathers;
    
    void turnAllOff();

    void setStateFromDesired();

    void setFeatherFromDesired();
  };
}
