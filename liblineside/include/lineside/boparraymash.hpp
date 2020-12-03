#pragma once

#include <map>
#include <vector>

#include "tendril/boparray.hpp"

#include "lineside/multiaspectsignalhead.hpp"

namespace Lineside {
  //! Implementation of a multiple aspect signal head using a BOPArray
  class BOPArrayMASH : public MultiAspectSignalHead {
  public:
    BOPArrayMASH(const ItemId signalHeadId) :
      MultiAspectSignalHead(signalHeadId),
      pins(),
      aspects(),
      feathers() {}

    virtual void OnActivate() override;

    virtual void OnDeactivate() override;

    virtual std::chrono::milliseconds OnRun() override;

    virtual unsigned int GetAspectCount() const override;

    virtual unsigned int GetFeatherCount() const override;

    std::unique_ptr<Tendril::BOPArray> pins;
  private:
    //! Mark all pins for off (but don't update)
    void markAllOff();
    
    //! Mapping of aspects to pins in the BOPArray
    std::map<SignalAspect,unsigned int> aspects;

    //! Link feathers to pins in the BOPArray
    std::vector<unsigned int> feathers;
  };
}
