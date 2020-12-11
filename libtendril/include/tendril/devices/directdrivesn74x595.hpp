#pragma once

#include <mutex>
#include <chrono>

#include "tendril/binaryoutputpin.hpp"
#include "tendril/boparray.hpp"
#include "tendril/hardwareprovider.hpp"

namespace Tendril::Devices {
  class DD595BOPArray;
  
  //! Class to represent directly driven chained SN74x595 shift registers
  class DirectDriveSN74x595 : public Device,
			      public HardwareProvider<BOPArray> {
  public:
    const std::chrono::nanoseconds DefaultLevelDelay = std::chrono::nanoseconds(10);
    
    //! Register with the HardwareManager
    virtual void Register(HardwareManager& hwManager) override;

    //! Fetch a BOPArray
    virtual std::unique_ptr<BOPArray>
    GetHardware(const std::string& hardwareId,
		const SettingsMap& settings) override;

    void EnableOutputs(bool enable);

    void Reset();

    void SetPinsAndSend(const std::map<unsigned int,bool>& pinUpdates);
    
    //! Delay to allow output pin level to stabilise
    /*!
      This is the delay between pin updates. For example,
      this is the delay imposed between the dataPin level being set
      and the clockPin being set to high. The clockPin will
      also then remain high for at least this long.
      
      Since this is passed to sleep() the exact wait is
      imprecise.
     */
    std::chrono::nanoseconds levelDelay;
  private:
    friend class DD595BOPArray;

    std::mutex updateMutex;

    std::unique_ptr<BinaryOutputPin> clockPin;
    std::unique_ptr<BinaryOutputPin> dataPin;
    std::unique_ptr<BinaryOutputPin> latchPin;
    std::unique_ptr<BinaryOutputPin> enablePin;
    std::unique_ptr<BinaryOutputPin> clearPin;

    std::vector<bool> state;
    std::vector<unsigned int> allocatedPins;
  };
}
