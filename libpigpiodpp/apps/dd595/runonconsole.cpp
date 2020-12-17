#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "runonconsole.hpp"

std::vector<unsigned int> ToBoolArray(const size_t value, const unsigned int numBits) {
  std::vector<unsigned int> result;
  result.resize(numBits);

  unsigned int iShift = 0;
  for( auto it=result.begin(); it!=result.end(); ++it ) {
    bool nxt = value & ( 1 << iShift );
    result.at(iShift) = nxt;
    
    iShift++;
  }

  for( auto it=result.begin(); it!=result.end(); ++it ) {
    std::cout << *it;
  }
  std::cout << std::endl;
  
  return result;
}

void RunOnConsole(Tendril::Devices::DirectDriveSN74x595& shifter) {
  std::cout << "Entering main loop" << std::endl;

  bool done = false;
  
  while( !done ) {
    std::string inputLine;
      
    std::getline( std::cin, inputLine );
    if( inputLine == "q" ) {
      std::cout << "Received quit" << std::endl;
      done = true;
    } else {
      try {
	size_t pattern = std::stoull(inputLine);

	auto values = ToBoolArray( pattern, shifter.totalPins );
	std::map<unsigned int,bool> updateRequest;
	for( unsigned int i=0; i<values.size(); ++i ) {
	  updateRequest[i] = values.at(i);
	}

	shifter.SetPinsAndSend( updateRequest );
      }
      catch( std::exception& e ) {
        std::cerr << e.what() << std::endl;
        continue;
      }      
    }
  }
}
