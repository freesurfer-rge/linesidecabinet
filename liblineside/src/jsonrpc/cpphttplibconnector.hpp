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
	: httpClient(host.c_str(), port) {}
      
      virtual std::string Send(const std::string &request) override;
      
    private:
      httplib::Client httpClient;
    };

    //! Server for JSON RPC
    class CppHttpLibServerConnector {
    public:
      explicit CppHttpLibServerConnector(jsonrpccxx::JsonRpcServer &server, int port);
      
      virtual ~CppHttpLibServerConnector() { StopListening(); }
      
      bool StartListening() {
	if (httpServer.is_running())
	  return false;
	this->thread = std::thread([this]() { this->httpServer.listen("localhost", port); });
	return true;
      }
      
      void StopListening() {
	if (httpServer.is_running()) {
	  httpServer.stop();
	  this->thread.join();
	}
      }
      
    private:
      std::thread thread;
      jsonrpccxx::JsonRpcServer &server;
      httplib::Server httpServer;
      int port;

      void PostAction(const httplib::Request &req, httplib::Response &res);
    };

  }
}
