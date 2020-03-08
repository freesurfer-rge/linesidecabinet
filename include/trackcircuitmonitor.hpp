#pragma once

#include "pwitemmodel.hpp"
#include "binaryinputpin.hpp"
#include "rtcclient.hpp"

namespace Lineside {
  class TrackCircuitMonitorData;

  class TrackCircuitMonitor : public PWItemModel {
  public:
    virtual void OnActivate() override;

    virtual void OnDeactivate() override;

    virtual std::chrono::milliseconds OnRun() override;

    virtual bool HaveStateChange() override;

    bool GetState() const;
  private:
    friend class TrackCircuitMonitorData;

    TrackCircuitMonitor(const ItemId tcmId) :
      PWItemModel(tcmId),
      monitorPin(),
      rtc() {}
    
    std::weak_ptr<BinaryInputPin> monitorPin;
    std::weak_ptr<RTCClient> rtc;
  };
}
