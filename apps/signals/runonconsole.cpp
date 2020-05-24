#include <string>
#include <vector>

#include "signalstate.hpp"
#include "signalflash.hpp"
#include "multiaspectsignalhead.hpp"
#include "utility.hpp"

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

void HandleMASH( Lineside::MultiAspectSignalHead& mash,
		 std::vector<std::string>& tokens ) {
  if( tokens.size() != 4 ) {
    std::cerr << __FUNCTION__ << ": Needs four tokens" << std::endl;
    return;
  }
  
  auto state = Lineside::Parse<Lineside::SignalState>(tokens.at(1));
  auto flash = Lineside::Parse<Lineside::SignalFlash>(tokens.at(2));
  auto feather = std::stoul(tokens.at(3));

  mash.SetState(state, flash, feather);
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
	Lineside::MultiAspectSignalHead& mash = dynamic_cast<Lineside::MultiAspectSignalHead&>(pwItem);
	HandleMASH( mash, tokens );
      }
      catch( std::exception& e ) {
	std::cerr << e.what() << std::endl;
	continue;
      }
      
    }
  }
}

