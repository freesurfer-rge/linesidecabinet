#pragma once

#include <memory>
#include "lineside/pwitemmanager.hpp"

#include "lineside/jsonrpc/cabinetservice.hpp"

namespace Lineside {
  namespace JsonRPC {
    //! Implementation of the CabinetService
    class CabinetServiceImpl : public CabinetService {
    public:
      CabinetServiceImpl(std::shared_ptr<const PWItemManager> itemManager);

      virtual
      CabinetServiceResponse
      SetMultiAspectSignal(const Lineside::ItemId id,
			   const Lineside::SignalState state,
			   const Lineside::SignalFlash flash,
			   const unsigned int feather) override;

      virtual
      CabinetServiceResponse
      SetTurnout(const Lineside::ItemId id,
		 const Lineside::TurnoutState state) override;

      virtual bool GetTrackCircuit(const Lineside::ItemId id) override;
    private:
      std::shared_ptr<const PWItemManager> pwim;
    };
  }
}
