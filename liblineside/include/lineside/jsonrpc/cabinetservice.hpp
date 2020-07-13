#pragma once

#include "lineside/itemid.hpp"
#include "lineside/signalstate.hpp"
#include "lineside/signalflash.hpp"
#include "lineside/turnoutstate.hpp"

namespace Lineside {
  namespace JsonRPC {
    //! Interface for use by the RPC side
    class CabinetService {
    public:
      virtual ~CabinetService() {}
      
      virtual bool SetMultiAspectSignal(const std::string id,
					const Lineside::SignalState state,
					const Lineside::SignalFlash flash,
					const unsigned int feather) = 0;

      virtual bool SetTurnout(const std::string id,
			      const Lineside::TurnoutState state) = 0;

      virtual bool GetTrackCircuit(const std::string id) = 0;
    };
  }
}
