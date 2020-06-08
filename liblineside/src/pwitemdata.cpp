#include <boost/predef.h>

#include "lineside/pwitemdata.hpp"

namespace Lineside {
#if defined(BOOST_COMP_GNUC)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#elif defined(BOOST_COMP_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif
  void PWItemData::UnusedSoftwareManager(const SoftwareManager& sw) const {
    // Do nothing
  }
#if defined(BOOST_COMP_GNUC)
#pragma GCC diagnostic pop
#elif defined(BOOST_COMP_CLANG)
#pragma clang diagnostic pop
#endif
  
}
