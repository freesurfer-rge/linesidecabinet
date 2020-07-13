#pragma once

#include "lineside/jsonrpc/cabinetservice.hpp"

#include <jsonrpccxx/server.hpp>

namespace Lineside {
  namespace JsonRPC {
    class RPCServer {
    public:
      RPCServer(std::shared_ptr<CabinetService> cabinet);

      jsonrpccxx::JsonRpc2Server& GetServer() {
	std::cerr << __FUNCTION__ << ": Needs better solution" << std::endl;
	return this->rpcServer;
      }
    private:
      std::shared_ptr<CabinetService> cabinet;
      jsonrpccxx::JsonRpc2Server rpcServer;
    };
  }
}
