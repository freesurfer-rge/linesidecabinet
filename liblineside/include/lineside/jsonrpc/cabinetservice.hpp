#pragma once

#include <functional>

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

      //! Function to set the state of a multiaspect signal
      virtual
      CabinetServiceResponse
      SetMultiAspectSignal(const Lineside::ItemId id,
			   const Lineside::SignalState state,
			   const Lineside::SignalFlash flash,
			   const unsigned int feather) = 0;

      //! Function to set the state of a turnout
      virtual
      CabinetServiceResponse
      SetTurnout(const Lineside::ItemId id,
		 const Lineside::TurnoutState state) = 0;

      //! Function to get the state of a track circuit
      virtual bool GetTrackCircuit(const Lineside::ItemId id) = 0;
    };
  }
}
