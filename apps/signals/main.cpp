#include <cstdlib>
#include <iostream>

#include "cmdlineopts.hpp"

int main(int argc, char* argv[]) {
  try {
    CmdLineOpts opts;
    opts.Populate(argc, argv);
    if( opts.helpMessagePrinted ) {
      return EXIT_SUCCESS;
    }
  }
  catch(std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
