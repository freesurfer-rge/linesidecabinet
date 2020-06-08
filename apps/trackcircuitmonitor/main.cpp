#include <iostream>
#include "pi/pihardwaremanager.hpp"
#include "xml/configurationreader.hpp"
#include "trackcircuitmonitordata.hpp"

#include "pwitemmanager.hpp"

#include "cmdlineopts.hpp"
#include "stubsoftwaremanager.hpp"

void CheckPWItems(const std::vector<std::shared_ptr<Lineside::PWItemData>>& pwItems) {
  for( auto it=pwItems.begin(); it!=pwItems.end(); ++it ) {
    auto signal = std::dynamic_pointer_cast<Lineside::TrackCircuitMonitorData>(*it);
    if( !signal ) {
      throw std::runtime_error("All PWItems must be of type TrackCircuitMonitor");
    }
  }
}

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
    auto sw = std::make_shared<StubSoftwareManager>();
    Lineside::PWItemManager pwItemManager( hw, sw );

    pwItemManager.CreatePWItems(config.pwItems);

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
  }
  catch(std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
