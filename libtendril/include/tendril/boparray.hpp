#pragma once

#include <vector>
#include "tendril/tendriltypes.hpp"

namespace Tendril {
  //! Abstraction for a collection of binary output pins which are updated together
  class BOPArray {
  public:
    //! Construct an instance of the class
    /*!
      @param nPins The number of pins in the array
     */
    BOPArray(const size_t nPins)
      : pinState(nPins) {}

    virtual ~BOPArray() {}

    //! Set the value of a pin
    /*!
      This only updates the internal request array.
      The hardware will only update when Update is called.

      @param i The index of the pin to be updated
      @param level The desired level for the pin
     */
    void Set(const size_t i, const bool level);

    //! Update the hardware
    /*!
      Implementations of this class should update the hardware
      using the internal pinState array when this method is called.
     */
    virtual void Update() = 0;

    //! Extract a list of pin ids from the SettingsMap
    /*!
      The settings for a BOPArray are expected to be of the form
      { "O":"GPIO10", "1":"GPIO03" ... }
      with the keys actually being sequential integers, and the
      values having meaning to the underlying HardwareProvider. Since
      these are binary outputs, there should be no other settings
      required.
    */
    static std::vector<std::string> ExtractPinList(const SettingsMap& settings);
  protected:
    //! The current requested state for the pins
    /*!
      An implementing class should use the values in this array to update the hardware
      when Update is called.
     */
    std::vector<bool> pinState;
  };
}
