#pragma once

namespace Lineside {
  //! Abstraction for something which can receive notifications
  template<typename NotificationType>
  class Notifiable {
  public:
    virtual ~Notifiable() {}
    
    //! Method to be called when some event occurs
    virtual void Notify(const unsigned int sourceId, const NotificationType notification) = 0;
  };
}
