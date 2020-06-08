#include "xercesc/util/PlatformUtils.hpp"

#include "lineside/xml/xercesguard.hpp"

namespace Lineside {
  namespace xml {
    XercesGuard::XercesGuard() {
      xercesc::XMLPlatformUtils::Initialize();
    }

    XercesGuard::~XercesGuard() {
      xercesc::XMLPlatformUtils::Terminate();
    }
  }
}
