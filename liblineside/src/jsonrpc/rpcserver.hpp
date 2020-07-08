#pragma once

#include "cabinetservice.hpp"

#include <jsonrpccxx/server.hpp>

namespace Lineside {
  namespace JsonRPC {
    class RPCServer {
    public:
      RPCServer();

    private:
      std::unique_ptr<CabinetService> cabinet;
      jsonrpccxx::JsonRpc2Server rpcServer;
    };
  }
}
