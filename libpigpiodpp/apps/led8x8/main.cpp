#include <cstdlib>
#include <iostream>
#include <memory>

#include "pigpiodpp/pimanager.hpp"
#include "pigpiodpp/pibopprovider.hpp"
#include "tendril/devices/directdrivesn74x164.hpp"

#include "cmdlineopts.hpp"
#include "runonconsole.hpp"


int main(int argc, char* argv[]) {
  std::cout << "Direct Drive for LED 8x8 Display" << std::endl;

  try {
    CmdLineOpts opts;
    opts.Populate(argc, argv);
    if( opts.helpMessagePrinted ) {
      return EXIT_SUCCESS;
    }

    auto pi = PiGPIOdpp::PiManager::CreatePiManager();
    auto provider = std::make_shared<PiGPIOdpp::PiBOPProvider>(pi);

    Tendril::SettingsMap emptySettings;
    auto wclk = provider->GetHardware(opts.wclkPin, emptySettings);
    auto data = provider->GetHardware(opts.dataPin, emptySettings);
    auto dclk = provider->GetHardware(opts.dclkPin, emptySettings);
    std::unique_ptr<Tendril::BinaryOutputPin> noConnect;
    
    const unsigned int shiftersInChain = 2;

    // Get the shifter
    auto shifter = std::make_shared<Tendril::Devices::DirectDriveSN74x164>("SN74x164",
									   shiftersInChain,
                                                                           dclk,
                                                                           data,
                                                                           noConnect);
    std::cout << "Created shifter, now creating registers" << std::endl;
    Tendril::SettingsMap bopaSettings;
    for( unsigned int i=0; i<shifter->pinsInChain; ++i ) {
      std::string mapping = std::to_string(i);
      bopaSettings[mapping] = mapping;
    }

    auto registerArray = shifter->GetHardware( "ShiftArray", bopaSettings );

    std::cout << "Setting wclk high" << std::endl;
    wclk->Set(true);

    // Enter the main loop
    RunOnConsole(*registerArray, *wclk);
  }
  catch( std::exception& e ) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
