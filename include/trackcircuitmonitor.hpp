#pragma once

#include <atomic>
#include <mutex>

#include "notifiable.hpp"
#include "pwitemmodel.hpp"
#include "binaryinputpin.hpp"
#include "rtcclient.hpp"

namespace Lineside {
  class TrackCircuitMonitorData;

  //! Class to monitor a track circuit and send notifications to rail traffic control
  class TrackCircuitMonitor : public PWItemModel, public Notifiable<bool> {
  public:
    const std::chrono::milliseconds SleepRequest = std::chrono::milliseconds(5000);
    
    virtual void OnActivate() override;

    virtual void OnDeactivate() override;

    virtual std::chrono::milliseconds OnRun() override;

    virtual bool HaveStateChange() override;

    bool GetState() const;

    virtual void Notify(const unsigned int sourceId, const bool notification) override;
  private:
    friend class TrackCircuitMonitorData;

    TrackCircuitMonitor(const ItemId tcmId) :
      PWItemModel(tcmId),
      updateMtx(),
      lastNotificationState(false),
      monitorPin(),
      rtc() {}

    std::mutex updateMtx;
    std::atomic<bool> lastNotificationState;
    std::weak_ptr<BinaryInputPin> monitorPin;
    std::weak_ptr<RTCClient> rtc;
  };
}
