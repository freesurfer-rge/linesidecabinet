#include "lineside/boparraymash.hpp"

namespace Lineside {
  unsigned int BOPArrayMASH::GetAspectCount() const {
    return this->aspects.size();
  }

  unsigned int BOPArrayMASH::GetFeatherCount() const {
    return this->feathers.size();
  }
}
