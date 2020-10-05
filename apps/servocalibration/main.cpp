#include <cstdlib>
#include <iostream>

#include "cmdlineopts.hpp"
#include "runonconsole.hpp"


int main(int argc, char* argv[]) {
  try {
    CmdLineOpts opts;
    opts.Populate(argc, argv);
    if( opts.helpMessagePrinted ) {
      return EXIT_SUCCESS;
    }

    Lineside::xml::ConfigurationReader cr;

    auto config = cr.Read(opts.configFilePath);
    CheckPWItems(config.pwItems);

    auto hw = std::make_shared<Lineside::Pi::PiHardwareManager>(config.hwManager);

    RunOnConsole(pwItemManager);
  }
  catch(std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
