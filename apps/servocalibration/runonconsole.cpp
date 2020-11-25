#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "runonconsole.hpp"


void RunOnConsole(Tendril::PWMChannel& servo) {
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
	int nextValue = std::stoi(inputLine);
	servo.Set(0, nextValue);
      }
      catch( std::exception& e ) {
	std::cerr << e.what() << std::endl;
	continue;
      }
    }
  }
}

