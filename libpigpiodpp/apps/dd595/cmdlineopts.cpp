#include <iostream>
#include <boost/program_options.hpp>

#include "cmdlineopts.hpp"

namespace bpo = boost::program_options;


void CmdLineOpts::Populate(int argc, char* argv[]) {
  const std::string clockOpt = "clock";
  const std::string clockOptDesc = "GPIO pin for clock";

  const std::string dataOpt = "data";
  const std::string dataOptDesc = "GPIO pin for data";

  const std::string latchOpt = "latch";
  const std::string latchOptDesc = "GPIO pin for latch";

  const std::string chainOpt = "chain";
  const std::string chainOptDesc = "Number of shift registers in chain";

  bpo::options_description desc("Allowed Options");
  desc.add_options()
    ("help", "Show help message")
    (clockOpt.c_str(), bpo::value<std::string>(&(this->clockPin)), clockOptDesc.c_str())
    (dataOpt.c_str(), bpo::value<std::string>(&(this->dataPin)), dataOptDesc.c_str())
    (latchOpt.c_str(), bpo::value<std::string>(&(this->latchPin)), latchOptDesc.c_str())
    (chainOpt.c_str(), bpo::value<int>(&(this->chainLength)), chainOptDesc.c_str())
    ;
  
  bpo::variables_map vm;
  bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
  bpo::notify(vm);

  if( vm.count("help") ) {
    std::cout << desc << std::endl;
    this->helpMessagePrinted = true;
    return;
  }
  
  if( vm.count(clockOpt.c_str()) ) {
    std::cout << "Clock pin: " << this->clockPin << std::endl;
  } else {
    throw std::runtime_error("Clock pin not specified");
  }
  
  if( vm.count(dataOpt.c_str()) ) {
    std::cout << "Data pin : " << this->dataPin << std::endl;
  } else {
    throw std::runtime_error("Data pin not specified");
  }

  if( vm.count(latchOpt.c_str()) ) {
    std::cout << "Latch pin: " << this->latchPin << std::endl;
  } else {
    throw std::runtime_error("Latch pin not specified");
  }

  if( vm.count(chainOpt.c_str()) ) {
    std::cout << "Devices in chain : " << this->chainLength << std::endl;
  } else {
    throw std::runtime_error("Device in chain not specified");
  }
}
