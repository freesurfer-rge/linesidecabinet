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
  //! Class to represent directly driven chained SIPO shift registers
  class DirectDriveSIPOShiftRegister : public Device,
				       public HardwareProvider<BOPArray> {
  public:
    const std::chrono::microseconds DefaultLevelDelay = std::chrono::microseconds(10);

    DirectDriveSIPOShiftRegister(const std::string deviceName,
				 const unsigned int pinsInChain,
				 std::unique_ptr<BinaryOutputPin>& clock,
				 std::unique_ptr<BinaryOutputPin>& data);

    //! Register with the HardwareManager
    virtual void Register(HardwareManager& hwManager) override;

    //! Fetch a BOPArray
    virtual std::unique_ptr<BOPArray>
    GetHardware(const std::string& hardwareId,
		const SettingsMap& settings) override;
    
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
    virtual
    std::chrono::microseconds getLevelDelay() const = 0;
    
    const unsigned int pinsInChain;
    
  protected:
    virtual void BeforeSend() = 0;

    virtual void AfterSend() = 0;

    std::mutex updateMutex;

  private:
    std::unique_ptr<BinaryOutputPin> clockPin;
    std::unique_ptr<BinaryOutputPin> dataPin;
    
    std::vector<bool> state;
    std::set<unsigned int> allocatedPins;
  };
}
