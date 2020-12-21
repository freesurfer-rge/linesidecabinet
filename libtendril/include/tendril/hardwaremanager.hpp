#pragma once

#include "tendril/registrar.hpp"
#include "tendril/hardwareprovider.hpp"
#include "tendril/hardwarerequestdata.hpp"
#include "tendril/binaryoutputpin.hpp"
#include "tendril/binaryinputpin.hpp"
#include "tendril/boparray.hpp"
#include "tendril/pwmchannel.hpp"
#include "tendril/i2ccommunicator.hpp"


//! Namespace for holding hardware abstractions
/*!
  The Tendril library facilitates interacting with
  attached hardware.
  Its functionality falls into three groups:

  - Abstractions to describe external hardware, such as the BinaryOutputPin
  - Mocks for use in tests
  - Devices which implement peripherals such as the PCA9685 chip (and which depend on the abstractions)

  This library is supposed to sit between code which wishes to interact with hardware (the _consuming_ library - Lineside is an example) and code which drives the hardware directly (the _implementing_ library - PiGPIOdpp is an example).
  The consuming library interacts at a high level with the abstractions - for instance requesting that an output pin be turned on or off.
  The implementing library provides concrete implementations of the abstractions, and actually turns the pin on and off.
  The pivot between the two libraries is the HardwareManager.
  At a high level, the implementing library populates the HardwareManager with information about the available hardware, and the consuming library then requests particular pieces of hardware.

  One underlying assumption which should be borne in mind: each piece of hardware is owned by exactly one object.
  This is seen in the ultimate types which the consuming library will receive - std::unique_ptr objects for the requested item.
 */
namespace Tendril {
  //! Class for managing hardware
  /*!
    This class mediates between the consuming and implementing libraries.
    The implementing library needs to provide a means of creating an instance of this class
    and populating it with information about the available hardware.
    The consuming library can then request the exact hardware required from that instance.
    Currently, four different types of hardware are supported:

    - Binary input pins
    - Binary output pins
    - Arrays of binary output pins
    - Pulse Width Modulation channels

    A Registrar is provided for each one.
   */
  class HardwareManager {
  public:
    HardwareManager() :
      i2cCommProviderRegistrar(),
      bopProviderRegistrar(),
      bipProviderRegistrar(),
      bopArrayProviderRegistrar(),
      pwmcProviderRegistrar() {}
    //! Get an I2CCommunicator from the registrar
    std::unique_ptr<I2CCommunicator>
    GetI2CComms(const HardwareRequestData& hrd);

    //! Get a BinaryOutputPin from the registrar
    std::unique_ptr<BinaryOutputPin>
    GetBOP(const HardwareRequestData& hrd);

    //! Registrar for providers of I2C communicators
    Registrar<HardwareProvider<I2CCommunicator>> i2cCommProviderRegistrar;
    
    //! Registrar for providers of binary output pins
    Registrar<HardwareProvider<BinaryOutputPin>> bopProviderRegistrar;

    //! Registrar for providers of binary input pins
    Registrar<HardwareProvider<BinaryInputPin>> bipProviderRegistrar;

    //! Registrar for providers of binary output pin arrays
    Registrar<HardwareProvider<BOPArray>> bopArrayProviderRegistrar;

    //! Registrar for providers of PWM channels
    Registrar<HardwareProvider<PWMChannel>> pwmcProviderRegistrar;
  };
}
