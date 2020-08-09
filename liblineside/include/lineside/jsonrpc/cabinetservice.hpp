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
      SetMultiAspectSignal(const Lineside::ItemId id,
			   const Lineside::SignalState state,
			   const Lineside::SignalFlash flash,
			   const unsigned int feather) = 0;
      
      virtual
      CabinetServiceResponse
      SetMultiAspectSignal(const std::string id,
			   const std::string state,
			   const std::string flash,
			   const unsigned int feather) = 0;

      virtual
      CabinetServiceResponse
      SetTurnout(const Lineside::ItemId id,
		 const Lineside::TurnoutState state) = 0;
      
      virtual
      CabinetServiceRespose
      SetTurnout(const std::string id,
		 const std::string state) = 0;

      virtual bool GetTrackCircuit(const Lineside::ItemId id) = 0;

      virtual bool GetTrackCircuit(const std::string id) = 0;
    };
  }
}
