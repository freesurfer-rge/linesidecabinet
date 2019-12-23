#pragma once

#include <string>
#include <map>
#include <memory>

namespace Lineside {
  //! An abstraction of a class which provides hardware access
  /*!
    \tparam Hardware The type of hardware which can be accessed
   */
  template<typename Hardware>
  class HardwareProvider {
  public:
    typedef Hardware HardwareType;

    virtual ~HardwareProvider() {}

    virtual std::shared_ptr<Hardware> GetHardware( const std::string& hardwareId,
						   const std::map<std::string,std::string>& settings ) = 0;
  };
}
