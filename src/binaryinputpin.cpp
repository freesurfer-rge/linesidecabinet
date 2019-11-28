#include "binaryinputpin.hpp"

namespace Lineside {
  bool BinaryInputPin::Wait() {
    std::atomic<bool> last;
    std::unique_lock<std::mutex> lck(this->mtx);
    last = this->Get();
    // Specify predicate function to guard against spurious wakeups
    this->cv.wait( lck, [this,&last](){ return last != this->Get(); } );
    return this->Get();
  }

  void BinaryInputPin::NotifyOneUpdate() {
    std::lock_guard<std::mutex> lg(this->mtx);
    this->cv.notify_one();
  }
}
