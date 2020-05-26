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
    const std::chrono::milliseconds SleepRequest = std::chrono::seconds(60);
    
    virtual void OnActivate() override;

    virtual void OnDeactivate() override;

    //! Unconditionally sends an update to rail traffic control
    virtual std::chrono::milliseconds OnRun() override;

    virtual bool HaveStateChange() override;

    //! Fetchs the current state of the monitored track circuit
    bool GetState() const;

    //! Method called when the monitored BinaryInputPin changes state
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
    std::unique_ptr<BinaryInputPin> monitorPin;
    std::shared_ptr<RTCClient> rtc;
  };
}
