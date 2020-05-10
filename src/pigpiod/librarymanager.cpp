#include <mutex>
#include <stdexcept>
#include <sstream>

#ifdef HAVE_PIGPIO
#include <pigpiod_if2.h>
#else
#include "pigpiod/pigpiodstubs.hpp"
#endif

#include "pigpiod/librarymanager.hpp"

namespace Lineside {
  namespace PiGPIOd {
    std::mutex LibraryManager::mtx;
    bool LibraryManager::initialised = false;

    LibraryManager::LibraryManager() : id(-1) {
      this->id = pigpio_start(nullptr, nullptr);
      if( this->id < 0 ) {
	std::stringstream msg;
	msg << "Could not connect to pigpiod."
	    << "Have you run 'sudo pigpiod' ?";
	throw std::logic_error(msg.str());
      }
    }

    LibraryManager::~LibraryManager() {
      pigpio_stop(this->id);
      this->id = -1;
      LibraryManager::initialised = false;
    }

    std::shared_ptr<LibraryManager> LibraryManager::CreateLibraryManager() {
      std::lock_guard<std::mutex> lck(LibraryManager::mtx);

      if( LibraryManager::initialised ) {
	std::stringstream msg;
	msg << __FUNCTION__
	    << ": Already initialised";
	throw std::logic_error(msg.str());
      }

      // Work around private constructor
      struct enabler : public LibraryManager {};
      
      auto result = std::make_shared<enabler>();
      LibraryManager::initialised  = true;

      return result;
    }
  }
}
