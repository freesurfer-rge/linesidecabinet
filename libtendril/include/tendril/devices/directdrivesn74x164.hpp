#pragma once

#pragma once

#include <mutex>
#include <chrono>
#include <set>
#include <vector>

#include "tendril/binaryoutputpin.hpp"
#include "tendril/boparray.hpp"
#include "tendril/hardwareprovider.hpp"

#include "tendril/devices/device.hpp"

namespace Tendril::Devices {
  //! Class to represent directly driven chained SN74x164 shift registers
  class DirectDriveSN74x164 : public Device,
			      public HardwareProvider<BOPArray> {
    const std::chrono::microseconds DefaultLevelDelay = std::chrono::microseconds(10);
    const unsigned int PinsPerChip = 8;

    DirectDriveSN74x164(const std::string deviceName,
			const unsigned int chainLength,
			std::unique_ptr<BinaryOutputPin>& clock,
			std::unique_ptr<BinaryOutputPin>& data,
			std::unique_ptr<BinaryOutputPin>& clear);

    //! Register with the HardwareManager
    virtual void Register(HardwareManager& hwManager) override;

    //! Fetch a BOPArray
    virtual std::unique_ptr<BOPArray>
    GetHardware(const std::string& hardwareId,
		const SettingsMap& settings) override;
    
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
    std::chrono::microseconds levelDelay;
    
    //! Total number of pins available for use
    const unsigned int totalPins;
  private:
    std::mutex updateMutex;

    std::unique_ptr<BinaryOutputPin> clockPin;
    std::unique_ptr<BinaryOutputPin> dataPin;
    std::unique_ptr<BinaryOutputPin> clearPin;
    
    std::vector<bool> state;
    std::set<unsigned int> allocatedPins;
  };
}
