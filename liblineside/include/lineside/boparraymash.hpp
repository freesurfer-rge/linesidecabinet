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

    /*
      Technically, the following ought to be private.
      However, doing that makes testing a lot more difficult
      and objects like this should be managed through
      the parent classes anyway
     */
    
    //! Access to the hardware
    std::unique_ptr<Tendril::BOPArray> pins;
    
    //! Mapping of aspects to pins in the BOPArray
    std::map<SignalAspect,unsigned int> aspects;

    //! Link feathers to pins in the BOPArray
    /*!
      Note that the first entry is always ignored, since
      calling SetState with 'feather' equal to zero turns
      all feathers off.
      However, the first entry must be present, or other logic
      will fail.
    */
    std::vector<unsigned int> feathers;
  private:
    //! Mark all pins for off (but don't Update)
    void markAllOff();

    //! Mark the appropriate aspect
    void setStateFromDesired();

    //! Mark the appropriate feather
    void setFeatherFromDesired();
  };
}
