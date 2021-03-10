#pragma once

#include <mutex>
#include <chrono>
#include <set>
#include <vector>

#include "tendril/binaryoutputpin.hpp"

#include "tendril/devices/directdrivesiposhiftregister.hpp"

namespace Tendril::Devices {
  //! Class to represent directly driven chained SN74x595 shift registers
  /*!
    The goal of this class is to allow the shift registers to be used
    to provide more output pins. It does not make the 'shift-by-one' operation
    publically available.
  */
  class DirectDriveSN74x595 : public DirectDriveSIPOShiftRegister {
  public:
    static const std::chrono::microseconds DefaultLevelDelay;
    static const unsigned int PinsPerChip = 8;
    
    DirectDriveSN74x595(const std::string deviceName,
			const unsigned int chainLength,
			std::unique_ptr<BinaryOutputPin>& clock,
			std::unique_ptr<BinaryOutputPin>& data,
			std::unique_ptr<BinaryOutputPin>& latch,
			std::unique_ptr<BinaryOutputPin>& enable,
			std::unique_ptr<BinaryOutputPin>& clear );
    void EnableOutputs(bool enable);

    void Reset();

    virtual
    std::chrono::microseconds getLevelDelay() const override;

    void setLevelDelay(const std::chrono::microseconds delay);
    
  protected:
    virtual void BeforeSend() override;

    virtual void AfterSend() override;
    
  private:
    std::chrono::microseconds levelDelay;
    
    std::unique_ptr<BinaryOutputPin> latchPin;
    std::unique_ptr<BinaryOutputPin> enablePin;
    std::unique_ptr<BinaryOutputPin> clearPin;
  };
}
