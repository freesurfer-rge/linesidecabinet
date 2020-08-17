#include <iostream>
#include <boost/program_options.hpp>

#include "cmdlineopts.hpp"

namespace bpo = boost::program_options;

void CmdLineOpts::Populate(int argc, char* argv[]) {
  const std::string configOpt = "configuration-file";
  const char configOptSingle = 'f';
  const std::string configOptDesc = "Path to configuration XML file";

  const std::string configOptSpec = configOpt + "," + configOptSingle;

  bpo::options_description desc("Allowed Options");
  desc.add_options()
    ("help", "Show help message")
    (configOptSpec.c_str(), bpo::value<std::string>(&(this->configFilePath)), configOptDesc.c_str())
    ;
  
  bpo::variables_map vm;
  bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
  bpo::notify(vm);
  
  if( vm.count("help") ) {
    std::cout << desc << std::endl;
    this->helpMessagePrinted = true;
    return;
  }

  if( vm.count(configOpt.c_str()) ) {
    std::cout << "Configuration file: " << this->configFilePath << std::endl;
  } else {
    throw std::runtime_error("Configuration file not specified");
  }

}

