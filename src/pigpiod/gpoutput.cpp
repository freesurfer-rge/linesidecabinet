#include "pigpiod/gpoutput.hpp"

namespace Lineside {
  namespace PiGPIOd {
    GPOutput::GPOutput(std::shared_ptr<GPIOPin> piPin) :
      pin(piPin) {}

    void GPOutput::Set(const bool level) {
      this->pin->Write(level);
    }

    bool GPOutput::Get() const {
      return this->pin->Read();
    }
  }
}
