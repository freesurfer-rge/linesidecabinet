#include <mutex>
#include <stdexcept>
#include <sstream>

#ifdef PIGPIODPP_HAVE_PIGPIO
#include <pigpiod_if2.h>
#else
#include "pigpiodstubs.hpp"
#endif

#include "pigpiodpp/gpiopin.hpp"
#include "pigpiodpp/i2cpi.hpp"

#include "pigpiodpp/pimanager.hpp"

namespace PiGPIOdpp {
  std::mutex PiManager::mtx;
  bool PiManager::initialised = false;

  PiManager::PiManager()
    : id(-1),
      assignedPins() {
    this->id = pigpio_start(nullptr, nullptr);
    if( this->id < 0 ) {
      std::stringstream msg;
      msg << "Could not connect to pigpiod."
	  << "Have you run 'sudo pigpiod' ?";
      throw std::logic_error(msg.str());
    }
  }
  
  PiManager::~PiManager() {
    pigpio_stop(this->id);
    this->id = -1;
    PiManager::initialised = false;
  }
  
  std::unique_ptr<GPIOPin> PiManager::GetGPIOPin(const unsigned int pinId) {
    return std::make_unique<GPIOPin>(this->shared_from_this(), pinId);
  }

  std::unique_ptr<I2CPi> PiManager::GetI2CPi(const unsigned int i2cBus,
					     const unsigned int i2cAddress) {
    return std::make_unique<I2CPi>(this->shared_from_this(), i2cBus, i2cAddress);
  }
  
  std::shared_ptr<PiManager> PiManager::CreatePiManager() {
    std::lock_guard<std::mutex> lck(PiManager::mtx);
    
    if( PiManager::initialised ) {
      std::stringstream msg;
      msg << __FUNCTION__
	  << ": Already initialised";
      throw std::logic_error(msg.str());
    }
    
    // Work around private constructor
    struct enabler : public PiManager {};
    
    auto result = std::make_shared<enabler>();
    PiManager::initialised  = true;
    
    return result;
  }
}
