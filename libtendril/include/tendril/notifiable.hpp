#pragma once

namespace Tendril {
  //! Something which can receive notifications
  /*!
    This collaborates with the Notifier class to provide call-back functionality.

    \tparam NotificationType The type of object for the notification message
   */
  template<typename NotificationType>
  class Notifiable {
  public:
    virtual ~Notifiable() {}

    //! Receive a notification
    /*!
      When there is a new notification, this method will be called

      @param notification The notification message
    */
    virtual void Notify(const NotificationType& notification) = 0;
  };
}
