#include <mutex>
#include <stdexcept>
#include <sstream>

#ifdef PIGPIODPP_HAVE_PIGPIO
#include <pigpiod_if2.h>
#else
#include "pigpiodstubs.hpp"
#endif

#include "pigpiodpp/gpiopin.hpp"

#include "pigpiodpp/pimanager.hpp"

namespace PiGPIOdpp {
  std::mutex PiManager::mtx;
  bool PiManager::initialised = false;

  PiManager::PiManager() : id(-1) {
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
    return std::unique_ptr<GPIOPin>(new GPIOPin(this->shared_from_this(), pinId));
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
