#pragma once

#include <memory>
#include <mutex>

namespace Lineside {
  namespace PiGPIOd {
    class GPIOPin;
    
    //! Class to wrap the <a href="http://abyz.me.uk/rpi/pigpio/pigpiod.html">pigpiod library</a>
    /*!
      This class is used to manage the calls to
      <a href="http://abyz.me.uk/rpi/pigpio/pdif2.html#pigpio_start">`pigio_start()`</a>
      and
      <a href="http://abyz.me.uk/rpi/pigpio/pdif2.html#pigpio_stop">`pigio_stop()`</a>
      in the
      <a href="http://abyz.me.uk/rpi/pigpio/pigpiod.html">pigpiod library</a>.
      
      A program wishing to access the pigpiod library should call the static method
      PiManager::CreatePiManager
      which returns a std::shared_ptr to an instance of a PiManager object.
      Copies of this std::shared_ptr can be given to other objects which want to interact
      with the Raspberry Pi.
      So long as at least one of these std::shared_ptr objects continues to exist, the
      pigpiod library will remain active.
      When the reference count of the std::shared_ptr reaches zero,
      <a href="http://abyz.me.uk/rpi/pigpio/pdif2.html#pigpio_stop">`pigio_stop()`</a>
      will be called to stop the library.
      
      This class relies on
      <a href="https://en.cppreference.com/w/cpp/memory/shared_ptr">
      the control block (which includes the reference count)
      </a>
      being thread safe, so that the destructor will be called exactly
      once (and that there isn't a race condition which can result in an
      attempted resurrection once the reference count gets to zero).
     */
    class PiManager : public std::enable_shared_from_this<PiManager> {
    public:
      ~PiManager();

      //! Get the identifier for the controlled Pi
      int getId() const {
	return this->id;
      }

      //! Get a GPIOPin for this Pi
      std::shared_ptr<GPIOPin> GetGPIOPin(const unsigned int pinId);
      
      //! Create an instance of PiManager
      /*!
	This creates an instance of a PiManager object in a std::shared_ptr and
	returns it.
	If the library has already been initialised, this will throw a std::logic_error
	exception.
       */
      static std::shared_ptr<PiManager> CreatePiManager();
    private:
      PiManager();

      //! The id of the Pi we are accessing (for use in other calls to the pigpiod library)
      int id;

      //! Indicates if the library has been initialised
      static bool initialised;

      //! Mutex to make operations thread safe
      static std::mutex mtx;
    };
  }
}
