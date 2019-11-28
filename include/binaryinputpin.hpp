#pragma once

#include <chrono>
#include <atomic>
#include <mutex>
#include <condition_variable>

namespace Lineside {
  //! Abstraction for a binary input pin
  /*!
    This class is more complex than Lineside::BinaryOutputPin since
    the program will have to respond to changes in the level.
   */
  class BinaryInputPin {
  public:
    BinaryInputPin() :
      mtx(),
      cv() {}
    
    virtual ~BinaryInputPin() {}

    //! Reads the current state of the pin
    virtual bool Get() const = 0;

    //! Blocks the current thread until NotifyOneUpdate is called
    bool Wait();

    //! Blocks the current thread for a specified duration or until NotifyOneUpdate is called
    template<class Rep, class Period>
    bool WaitFor(const std::chrono::duration<Rep,Period>& waitTime ) {
      std::atomic<bool> last;
      std::unique_lock<std::mutex> lck(this->mtx);
      last = this->Get();
      this->cv.wait_for( lck,
                         waitTime,
                         [this,&last](){ return last != this->Get(); } );
      return this->Get();
    }
  protected:
    void NotifyOneUpdate();
    
  private:
    std::mutex mtx;
    std::condition_variable cv;
  };
}
