#include "pigpiod/gpoutput.hpp"

namespace Lineside {
  namespace PiGPIOd {
    GPOutput::GPOutput(std::unique_ptr<GPIOPin> piPin) :
      pin(std::move(piPin)) {
      this->pin->SetMode(GPIOMode::Output);
      this->Set(false);
    }

    void GPOutput::Set(const bool level) {
      this->pin->Write(level);
    }

    bool GPOutput::Get() const {
      return this->pin->Read();
    }
  }
}
