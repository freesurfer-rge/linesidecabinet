#pragma once

#include "lineside/jsonrpc/cabinetservice.hpp"

namespace Lineside {
  namespace JsonRPC {
    //! Implementation of the CabinetService
    class CabinetServiceImpl : public CabinetService {
    public:
      CabinetServiceImpl();

      virtual
      CabinetServiceResponse
      SetMultiAspectSignal(const std::string id,
			   const Lineside::SignalState state,
			   const Lineside::SignalFlash flash,
			   const unsigned int feather) override;

      virtual
      CabinetServiceResponse
      SetTurnout(const std::string id,
		 const Lineside::TurnoutState state) override;

      virtual bool GetTrackCircuit(const std::string id) override;
    };
  }
}
