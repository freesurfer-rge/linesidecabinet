#pragma once

#include "tendril/registrar.hpp"
#include "tendril/hardwareprovider.hpp"
#include "tendril/binaryoutputpin.hpp"
#include "tendril/binaryinputpin.hpp"
#include "tendril/boparray.hpp"
#include "tendril/pwmchannel.hpp"


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
 */
namespace Tendril {
  //! Class for managing hardware
  class HardwareManager {
  public:
    HardwareManager() :
      bopProviderRegistrar(),
      bipProviderRegistrar(),
      bopArrayProviderRegistrar(),
      pwmcProviderRegistrar() {}

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
