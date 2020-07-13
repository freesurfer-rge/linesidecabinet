#pragma once

#include "lineside/itemid.hpp"
#include "lineside/signalstate.hpp"
#include "lineside/signalflash.hpp"
#include "lineside/turnoutstate.hpp"

#include "lineside/jsonrpc/cabinetserviceresponse.hpp"

namespace Lineside {
  namespace JsonRPC {
    //! Interface for use by the RPC side
    class CabinetService {
    public:
      virtual ~CabinetService() {}
      
      virtual
      CabinetServiceResponse
      SetMultiAspectSignal(const std::string id,
			   const Lineside::SignalState state,
			   const Lineside::SignalFlash flash,
			   const unsigned int feather) = 0;
      
      virtual
      CabinetServiceResponse
      SetTurnout(const std::string id,
		 const Lineside::TurnoutState state) = 0;

      virtual bool GetTrackCircuit(const std::string id) = 0;
    };
  }
}
