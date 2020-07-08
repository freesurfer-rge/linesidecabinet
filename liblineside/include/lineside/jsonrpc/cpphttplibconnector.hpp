#pragma once

#include <httplib.h>
#include <jsonrpccxx/iclientconnector.hpp>
#include <jsonrpccxx/server.hpp>
#include <string>

namespace Lineside {
  namespace JsonRPC {

    //! Client for JSON RPC
    class CppHttpLibClientConnector : public jsonrpccxx::IClientConnector {
    public:
      explicit CppHttpLibClientConnector(const std::string &host, int port)
	: jsonrpccxx::IClientConnector(),
	  httpClient(host.c_str(), port) {}
      
      virtual std::string Send(const std::string &request) override;
      
    private:
      httplib::Client httpClient;
    };

    //! Server for JSON RPC
    class CppHttpLibServerConnector {
    public:
      explicit CppHttpLibServerConnector(jsonrpccxx::JsonRpcServer& server,
					 std::string listenInterface,
					 int port);
      
      virtual ~CppHttpLibServerConnector() {
	this->StopListening();
      }
      
      bool StartListening();
      
      void StopListening();
      
    private:
      std::mutex listenMtx;
      std::thread thread;
      jsonrpccxx::JsonRpcServer& server;
      httplib::Server httpServer;
      std::string listenInterface;
      int port;

      void PostAction(const httplib::Request &req, httplib::Response &res);
    };

  }
}
