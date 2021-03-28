#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>

#include "runonconsole.hpp"

const unsigned int totalRegisterBits = 16;
const unsigned int maxValue = 256;
const unsigned int maxRow = 8;

std::vector<unsigned int> ToBoolArray(const size_t value, const unsigned int numBits) {
  std::vector<unsigned int> result;
  result.resize(numBits);

  unsigned int iShift = 0;
  for( auto it=result.rbegin(); it!=result.rend(); ++it ) {
    bool nxt = value & ( 1 << iShift );
    *it = nxt;
    
    iShift++;
  }

  for( auto it=result.begin(); it!=result.end(); ++it ) {
    std::cout << *it;
  }
  std::cout << std::endl;
  
  return result;
}


// ==========================================

void SetRow(const unsigned int row,
	    const unsigned int value,
	    Tendril::BOPArray& registers,
	    Tendril::BinaryOutputPin& wclk) {
  if( value >= maxValue ) {
    throw std::runtime_error("Value too large");
  }
  if( row >= maxRow ) {
    throw std::runtime_error("Row too large");
  }
  
  // Calculate the values to send to the shift registers
  auto bits = ToBoolArray(value + (row*maxValue), totalRegisterBits);
  
  // Update the registers
  std::map<unsigned int,bool> updateRequest;
  for( unsigned int i=0; i<bits.size(); ++i ) {
    registers.Set(i, bits.at(i));
  }
  registers.Update();
  
  // Pulse the clock
  wclk.Set(false);
  wclk.Set(true);
}


// ==========================================


void RunOnConsole(Tendril::BOPArray& registers, Tendril::BinaryOutputPin& wclk) {
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
	if( inputLine.at(0) == 'r' ) {
	  inputLine.at(0) = ' ';
	  std::stringstream l(inputLine);
	  unsigned int row, value;
	  l >> row >> value;

	  SetRow( row, value, registers, wclk );
	} else if( inputLine.at(0) == 'a' ) {
	  inputLine.at(0) = ' ';
	  std::stringstream l(inputLine);
	  for( unsigned int i=0; i<maxRow; i++ ) {
	    unsigned int nxtValue;
	    l >> nxtValue;

	    SetRow(i, nxtValue, registers, wclk );
	  }
	}
      }
      catch( std::exception& e ) {
        std::cerr << e.what() << std::endl;
        continue;
      } 
    }
  }
}
