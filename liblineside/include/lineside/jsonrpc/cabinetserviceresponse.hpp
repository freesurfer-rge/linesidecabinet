#pragma once

namespace Lineside {
  namespace JsonRPC {
    //! Enum for responses update instructions to a cabinet
    /*!
      We have this because a JSON-RPC notification can't even
      return an error code, even if the called routine throws
      an exception.
      By returning a value of this type (which will always indicate
      success), if there is an exception, it will be communicated back
      as a server error.
     */
    enum class CabinetServiceResponse { Success };
  }
}
