#include <cstdlib>
#include <iostream>
#include <memory>

#include "pigpiodpp/pimanager.hpp"
#include "pigpiodpp/pibopprovider.hpp"
#include "tendril/devices/directdrivesn74x595.hpp"

#include "cmdlineopts.hpp"

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

    Tendril::Devices::DirectDriveSN74x595 shifter("SN74x595",
						  opts.chainLength,
						  clk, data, ltch, noConnect, noConnect);
  }
  catch( std::exception& e ) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
