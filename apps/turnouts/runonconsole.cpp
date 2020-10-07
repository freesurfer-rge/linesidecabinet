#include <string>
#include <vector>

#include "lineside/turnoutstate.hpp"
#include "lineside/turnoutmotor.hpp"

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


void RunOnConsole(Lineside::PWItemManager& pwItemManager) {
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

      Lineside::ItemId target;

      try {
	target.Parse(tokens.at(0));

	Lineside::PWItemModel& pwItem = pwItemManager.GetPWItemModelById(target);
	Lineside::TurnoutMotor& to = dynamic_cast<Lineside::TurnoutMotor&>(pwItem);
	Lineside::TurnoutState state;
	state = Lineside::Parse<Lineside::TurnoutState>(tokens.at(1));
	to.SetState(state);
      }
      catch( std::exception& e ) {
	std::cerr << e.what() << std::endl;
	continue;
      }
      
    }
  }
}

