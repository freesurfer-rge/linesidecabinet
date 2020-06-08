#pragma once

#include <vector>
#include <memory>

#include "lineside/notifier.hpp"

namespace Lineside {
  //! Abstraction for a binary input pin
  /*!
    This class is more complex than Lineside::BinaryOutputPin since
    the program will have to respond to changes in the level.
   */
  class BinaryInputPin {
  public:
    
    BinaryInputPin() :
      notifier() {}
    
    virtual ~BinaryInputPin() {}

    //! Reads the current state of the pin
    virtual bool Get() const = 0;

    void RegisterListener(const unsigned int requestedSourceId,
			  std::weak_ptr<Notifiable<bool>> listener);
    
  protected:
    void NotifyUpdate();
    
  private:
    Notifier<bool> notifier;
  };
}