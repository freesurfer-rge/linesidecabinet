#pragma once

namespace Tendril {
  //! Something which can receive notifications
  template<typename NotificationType>
  class Notifiable {
  public:
    virtual ~Notifiable() {}
    
    virtual void Notify(const NotificationType& notification) = 0;
  };
}
