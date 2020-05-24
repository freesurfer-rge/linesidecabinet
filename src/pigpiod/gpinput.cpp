#include <boost/predef.h>

#include "pigpiod/gpinput.hpp"

namespace Lineside {
  namespace PiGPIOd {
    GPInput::GPInput(std::unique_ptr<GPIOPin> piPin,
		     GPIOPull pull,
		     unsigned int glitchSteadyMicroseconds,
		     GPIOEdge callBackEdge) :
      pin(std::move(piPin)) {
      this->pin->SetMode(GPIOMode::Input);
      this->pin->SetPUDResistor(pull);
      this->pin->SetGlitchFilter(glitchSteadyMicroseconds);

      auto callback = [this](const bool level) {
			this->ReceiveUpdate(level);
		      };
      this->pin->SetCallBack(callBackEdge, callback);
    }
    
#if defined(BOOST_COMP_GNUC)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#elif defined(BOOST_COMP_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif
    void GPInput::ReceiveUpdate(const bool level) {
      this->NotifyUpdate();
    }
#if defined(BOOST_COMP_GNUC)
#pragma GCC diagnostic pop
#elif defined(BOOST_COMP_CLANG)
#pragma clang diagnostic pop
#endif
    
    bool GPInput::Get() const {
      return this->pin->Read();
    }
  }
}
