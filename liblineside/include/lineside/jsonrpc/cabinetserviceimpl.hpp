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
      SetMultiAspectSignal(const Lineside::ItemId id,
			   const Lineside::SignalState state,
			   const Lineside::SignalFlash flash,
			   const unsigned int feather) override;
      
      virtual
      CabinetServiceResponse
      SetMultiAspectSignalString(const std::string id,
				 const std::string state,
				 const std::string flash,
				 const unsigned int feather) override;

      virtual
      CabinetServiceResponse
      SetTurnout(const Lineside::ItemId id,
		 const Lineside::TurnoutState state) override;
      
      virtual
      CabinetServiceResponse
      SetTurnoutString(const std::string id,
		       const std::string state) override;

      virtual bool GetTrackCircuit(const Lineside::ItemId id) override;

      virtual bool GetTrackCircuitString(const std::string id) override;
    };
  }
}
