#include <iostream>

#include "lineside/jsonrpc/rpcserver.hpp"
#include "lineside/jsonrpc/cpphttplibconnector.hpp"


/*
  Some sample calls
  
  Outstanding Issues:
  - Only GetTrackCircuit is working due to issue in the JSON parsing
    json-rpc-cxx is seeing the string "DoubleYellow" and not noticing that
    it can convert that to the appropriate type. The only reason that
    GetTrackCircuit is working is that the id argument is of type string, and
    is converted internally by GetTrackCircuit
  - All three methods are configured as RPC methods, rather than notifications
    This is indicated by the fact that they have an "id" field in the request
    and a non-void return type. This is because RPC notifications cannot even
    return errors:
    https://www.jsonrpc.org/specification#notification
    Currently, the return types are all bool; should improve this

  curl http://localhost:8483/jsonrpc -H "Content-Type application/json" --data '{ "method":"SetMultiAspectSignal", "params":{"id":"00:1a:2b:3c", "state":"DoubleYellow", "flash":"Steady", "feather":0}, "jsonrpc": "2.0" }'

  curl http://localhost:8483/jsonrpc -H "Content-Type application/json" --data '{ "method":"SetTurnout", "params":{"id":"00:1a:2b:3c", "state":"Straight"}, "id":1, "jsonrpc": "2.0" }'

  curl http://localhost:8483/jsonrpc -H "Content-Type application/json" --data '{ "method":"GetTrackCircuit", "params":{"id":"00:1a:2b:3c"}, "id":1, "jsonrpc": "2.0" }'
*/

int main() {
  std::cout << "Lineside Cabinet" << std::endl;
  std::cout << "================" << std::endl;
  std::cout << std::endl;

  Lineside::JsonRPC::RPCServer rpcServer;

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

  return 0;
}
