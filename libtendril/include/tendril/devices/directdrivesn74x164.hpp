#pragma once

#pragma once

#include <mutex>
#include <chrono>
#include <set>
#include <vector>

#include "tendril/binaryoutputpin.hpp"

#include "tendril/devices/directdrivesiposhiftregister.hpp"

namespace Tendril::Devices {
  //! Class to represent directly driven chained SN74x164 shift registers
  class DirectDriveSN74x164 : public DirectDriveSIPOShiftRegister {
  public:
    static const std::chrono::microseconds DefaultLevelDelay;
    static const unsigned int PinsPerChip = 8;

    DirectDriveSN74x164(const std::string deviceName,
			const unsigned int chainLength,
			std::unique_ptr<BinaryOutputPin>& clock,
			std::unique_ptr<BinaryOutputPin>& data,
			std::unique_ptr<BinaryOutputPin>& clear);

    void Reset();
    
    virtual
    std::chrono::microseconds getLevelDelay() const override;

    void setLevelDelay(const std::chrono::microseconds delay);

  protected:
    virtual void BeforeSend() override;

    virtual void AfterSend() override;
    
  private:
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

    std::unique_ptr<BinaryOutputPin> clearPin;
  };
}
