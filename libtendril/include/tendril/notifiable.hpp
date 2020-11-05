#pragma once

namespace Tendril {
  //! Something which can receive notifications
  template<typename T>
  class Notifiable {
  public:
    typedef T NotificationType;
    
    virtual ~Notifiable() {}
    
    virtual void Notify(const NotificationType notification) = 0;
  };
}
