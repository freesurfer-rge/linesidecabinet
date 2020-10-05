#include <string>
#include <vector>

#include "runonconsole.hpp"

std::vector<std::string>  stringtotokens( const std::string s) {
  std::vector<std::string> tokens;
  std::stringstream nxt;
  
  for( auto c=s.begin(); c!=s.end(); ++c ) {
    if( std::isspace(*c) ) {
      if( nxt.tellp() != 0 ) {
	// Just completed a token
	tokens.push_back(nxt.str());
	nxt.str(std::string());
      }
    } else {
      nxt << (*c);
    }
  }
  // Need to catch case where token ends line
  if( nxt.tellp() != 0 ) {
    // Just completed a token
    tokens.push_back(nxt.str());
  }
  
  return tokens;
}


void RunOnConsole() {
  std::cout << "Entering main loop" << std::endl;

  bool done = false;

  while( !done ) {
    std::string inputLine;
      
    std::getline( std::cin, inputLine );
    if( inputLine == "q" ) {
      std::cout << "Received quit" << std::endl;
      done = true;
    } else {
      auto tokens = stringtotokens(inputLine);

      try {
      }
      catch( std::exception& e ) {
	std::cerr << e.what() << std::endl;
	continue;
      }
      
    }
  }
}

