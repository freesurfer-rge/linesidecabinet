#include <iostream>

#include "lineside/pi/pihardwaremanager.hpp"
#include "lineside/xml/configurationreader.hpp"

#include "lineside/pwitemmanager.hpp"

#include "cmdlineopts.hpp"
#include "stubsoftwaremanager.hpp"

#include "lineside/jsonrpc/rpcserver.hpp"
#include "lineside/jsonrpc/cpphttplibconnector.hpp"
#include "lineside/jsonrpc/cabinetserviceimpl.hpp"

/*
  Some sample calls
  
  Outstanding Issues:
  - All three methods are configured as RPC methods, rather than notifications
    This is indicated by the fact that they have an "id" field in the request
    and a non-void return type. This is because RPC notifications cannot even
    return errors:
    https://www.jsonrpc.org/specification#notification
    Currently, the return types are all bool; should improve this

  curl http://localhost:8483/jsonrpc -H "Content-Type application/json" --data '{ "method":"SetMultiAspectSignal", "params":{"id":"00:1a:2b:3c", "state":"DoubleYellow", "flash":"Steady", "feather":0}, "id":1, "jsonrpc": "2.0" }'

  curl http://localhost:8483/jsonrpc -H "Content-Type application/json" --data '{ "method":"SetTurnout", "params":{"id":"00:1a:2b:3c", "state":"Straight"}, "id":1, "jsonrpc": "2.0" }'

  curl http://localhost:8483/jsonrpc -H "Content-Type application/json" --data '{ "method":"GetTrackCircuit", "params":{"id":"00:1a:2b:3c"}, "id":1, "jsonrpc": "2.0" }'
*/

int main(int argc, char* argv[]) {
  std::cout << "Lineside Cabinet" << std::endl;
  std::cout << "================" << std::endl;
  std::cout << std::endl;

  try {
    CmdLineOpts opts;
    opts.Populate(argc, argv);
    if( opts.helpMessagePrinted ) {
      return EXIT_SUCCESS;
    }

    Lineside::xml::ConfigurationReader cr;
    
    auto config = cr.Read(opts.configFilePath);
    
    auto hw = std::make_shared<Lineside::Pi::PiHardwareManager>(config.hwManager);
    auto sw = std::make_shared<StubSoftwareManager>();
    auto pwItemManager = std::make_shared<Lineside::PWItemManager>( hw, sw );
    
    pwItemManager->CreatePWItems(config.pwItems);
  
    auto csi = std::make_shared<Lineside::JsonRPC::CabinetServiceImpl>(pwItemManager);
    
    Lineside::JsonRPC::RPCServer rpcServer(csi);

    Lineside::JsonRPC::CppHttpLibServerConnector httpServer(rpcServer.GetServer(),
							    "0.0.0.0",
							    8483);
    
    std::cout << "Starting http server: "
	      << std::boolalpha << httpServer.StartListening()
	      << std::endl;
    
    std::cout << "Entering main loop" << std::endl;
    std::cout << "Type q to quit" << std::endl;
    bool done = false;
    while( !done ) {
      std::string inputLine;
      std::getline( std::cin, inputLine );
      if( inputLine == "q" ) {
	std::cout << "Received quit" << std::endl;
	done = true;
      }
    }
  }
  catch(std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return 0;
}
