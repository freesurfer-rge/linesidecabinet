#include <cstdlib>
#include <iostream>
#include <memory>

#include "pigpiodpp/pimanager.hpp"
#include "pigpiodpp/pibopprovider.hpp"
#include "tendril/devices/directdrivesn74x595.hpp"

#include "cmdlineopts.hpp"
#include "runonconsole.hpp"

int main(int argc, char* argv[]) {
  std::cout << "Tester for directly driven SN74x595" << std::endl;

  try {
    CmdLineOpts opts;
    opts.Populate(argc, argv);
    if( opts.helpMessagePrinted ) {
      return EXIT_SUCCESS;
    }

    auto pi = PiGPIOdpp::PiManager::CreatePiManager();
    auto provider = std::make_shared<PiGPIOdpp::PiBOPProvider>(pi);

    Tendril::SettingsMap emptySettings;
    auto clk = provider->GetHardware(opts.clockPin, emptySettings);
    auto data = provider->GetHardware(opts.dataPin, emptySettings);
    auto ltch = provider->GetHardware(opts.latchPin, emptySettings);
    std::unique_ptr<Tendril::BinaryOutputPin> noConnect;

    auto shifter = std::make_shared<Tendril::Devices::DirectDriveSN74x595>("SN74x595",
									   opts.chainLength,
									   clk,
									   data,
									   ltch,
									   noConnect,
									   noConnect);
    
    std::cout << "Created shifter, now creating BOPArray" << std::endl;
    
    Tendril::SettingsMap bopaSettings;
    for( unsigned int i=0; i<shifter->totalPins; ++i ) {
      std::string mapping = std::to_string(i);
      bopaSettings[mapping] = mapping;
    }

    auto bopArray = shifter->GetHardware( "ShiftArray", bopaSettings );

    RunOnConsole(*bopArray, shifter->totalPins);
  }
  catch( std::exception& e ) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
