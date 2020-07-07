#pragma once

#include <jsonrpccxx/server.hpp>

#include "lineside/itemid.hpp"
#include "lineside/signalstate.hpp"
#include "lineside/signalflash.hpp"

namespace Lineside {
  namespace JsonRPC {
    class CabinetServer {
    public:
      CabinetServer();
      
      void SetMultiAspectSignal(const Lineside::ItemId id,
				const Lineside::SignalState state,
				const Lineside::SignalFlash flash,
				const unsigned int feather);
    private:
      jsonrpccxx::JsonRpc2Server rpcServer;
    };
  }
}
