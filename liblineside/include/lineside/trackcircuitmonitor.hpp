#pragma once

#include <atomic>
#include <mutex>

#include "tendril/notifiable.hpp"
#include "tendril/binaryinputpin.hpp"

#include "lineside/pwitemmodel.hpp"
#include "lineside/rtcclient.hpp"
#include "lineside/trackcircuitsensor.hpp"

namespace Lineside {
  class TrackCircuitMonitorData;

  //! Class to monitor a track circuit and send notifications to rail traffic control
  class TrackCircuitMonitor : public PWItemModel, public Tendril::Notifiable<bool> {
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
    virtual void Notify(const bool& notification) override;
  private:
    friend class TrackCircuitMonitorData;

    TrackCircuitMonitor(const ItemId tcmId, const TrackCircuitSensor sensor) :
      PWItemModel(tcmId),
      updateMtx(),
      lastNotificationState(false),
      monitorPin(),
      rtc(),
      sensor(sensor) {}

    std::mutex updateMtx;
    std::atomic<bool> lastNotificationState;
    std::unique_ptr<Tendril::BinaryInputPin> monitorPin;
    std::shared_ptr<RTCClient> rtc;
    const TrackCircuitSensor sensor;
  };
}
