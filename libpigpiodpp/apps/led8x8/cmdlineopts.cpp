#include <iostream>
#include <boost/program_options.hpp>

#include "cmdlineopts.hpp"

namespace bpo = boost::program_options;


void CmdLineOpts::Populate(int argc, char* argv[]) {
  const std::string wclkOpt = "wclk";
  const std::string wclkOptDesc = "GPIO pin for wclk";

  const std::string dataOpt = "data";
  const std::string dataOptDesc = "GPIO pin for data";

  const std::string dclkOpt = "dclk";
  const std::string dclkOptDesc = "GPIO pin for dclk";

  bpo::options_description desc("Allowed Options");
  desc.add_options()
    ("help", "Show help message")
    (wclkOpt.c_str(), bpo::value<std::string>(&(this->wclkPin)), wclkOptDesc.c_str())
    (dataOpt.c_str(), bpo::value<std::string>(&(this->dataPin)), dataOptDesc.c_str())
    (dclkOpt.c_str(), bpo::value<std::string>(&(this->dclkPin)), dclkOptDesc.c_str())
    ;
  
  bpo::variables_map vm;
  bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
  bpo::notify(vm);

  if( vm.count("help") ) {
    std::cout << desc << std::endl;
    this->helpMessagePrinted = true;
    return;
  }
  
  if( vm.count(wclkOpt.c_str()) ) {
    std::cout << "wclk pin: " << this->wclkPin << std::endl;
  } else {
    throw std::runtime_error("wclk pin not specified");
  }
  
  if( vm.count(dataOpt.c_str()) ) {
    std::cout << "Data pin : " << this->dataPin << std::endl;
  } else {
    throw std::runtime_error("Data pin not specified");
  }

  if( vm.count(dclkOpt.c_str()) ) {
    std::cout << "dclk pin: " << this->dclkPin << std::endl;
  } else {
    throw std::runtime_error("dclk pin not specified");
  }
}
