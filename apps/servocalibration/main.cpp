#include <cstdlib>
#include <iostream>

#include "lineside/pwmchannel.hpp"
#include "lineside/pi/pihardwaremanager.hpp"
#include "lineside/xml/configurationreader.hpp"

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

    auto hw = std::make_shared<Lineside::Pi::PiHardwareManager>(config.hwManager);

    auto provider = hw->pwmcProviderRegistrar.Retrieve(opts.device);
    std::map<std::string,std::string> settings;
    auto servo = provider->GetHardware(std::to_string(opts.channel),
				       settings);
    
    RunOnConsole();
  }
  catch(std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
