#pragma once

#include "lineside/itemid.hpp"
#include "lineside/signalstate.hpp"
#include "lineside/signalflash.hpp"
#include "lineside/turnoutstate.hpp"

namespace Lineside {
  namespace JsonRPC {
    class CabinetService {
    public:
      CabinetService();

      /*
	All have non-void return in order to ensure we get errors back
       */
      
      bool SetMultiAspectSignal(const std::string id,
				const Lineside::SignalState state,
				const Lineside::SignalFlash flash,
				const unsigned int feather);

      bool SetTurnout(const std::string id,
		      const Lineside::TurnoutState state);

      bool GetTrackCircuit(const std::string id);
		      
    private:
    };
  }
}
