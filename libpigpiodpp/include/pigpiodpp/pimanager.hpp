#pragma once

#include <array>
#include <memory>
#include <mutex>
#include <set>

namespace PiGPIOdpp {
  class GPIOPin;
  class I2CPi;
  
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
    //! Number of GPIO pins
    const unsigned int nPins = 28;

    //! GPIO pins used by I2C Buses
    const std::array<std::set<unsigned int>,2> i2cBusPins {
      std::set<unsigned int>{0, 1},
      std::set<unsigned int>{2, 3}
    };
    
    ~PiManager();
    
    //! Get the identifier for the controlled Pi
    int getId() const {
      return this->id;
    }
    
    //! Get a GPIOPin for this Pi
    std::unique_ptr<GPIOPin> GetGPIOPin(const unsigned int pinId);

    //! Get an I2CDevice for this Pi
    std::unique_ptr<I2CPi> GetI2CPi(const unsigned int i2cBus,
				    const unsigned int i2cAddress);
    
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

    //! The pins requested so far
    std::set<unsigned int> assignedPins;

    //! I2CDevices
    std::array<std::set<unsigned int>, 2> i2cDevices;

    //! Reserve a pin (or throw)
    void ReservePin(unsigned int pin);
    
    //! Indicates if the library has been initialised
    static bool initialised;
    
    //! Mutex to make operations thread safe
    static std::mutex mtx;
  };
}
