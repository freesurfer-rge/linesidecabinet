#include <iostream>
#include <boost/program_options.hpp>

#include "cmdlineopts.hpp"

namespace bpo = boost::program_options;

void CmdLineOpts::Populate(int argc, char* argv[]) {
  const std::string configOpt = "configuration-file";
  const char configOptSingle = 'f';
  const std::string configOptDesc = "Path to configuration XML file";
  const std::string configOptSpec = configOpt + "," + configOptSingle;

  const std::string deviceOpt = "device";
  const char deviceOptSingle = 'd';
  const std::string deviceOptDesc = "Device to select from configuration file";
  const std::string deviceOptSpec = deviceOpt + "," + deviceOptSingle;
  
  const std::string channelOpt = "channel";
  const char channelOptSingle = 'c';
  const std::string channelOptDesc = "Channel on device to calibrate";
  const std::string channelOptSpec = channelOpt + "," + channelOptSingle;

  bpo::options_description desc("Allowed Options");
  desc.add_options()
    ("help", "Show help message")
    (configOptSpec.c_str(), bpo::value<std::string>(&(this->configFilePath)), configOptDesc.c_str())
    (deviceOptSpec.c_str(), bpo::value<std::string>(&(this->device)), deviceOptDesc.c_str())
    (channelOptSpect.c_str(), bpo::value<unsigned char>(&(this->channel)), channelOptDesc.c_str())
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

  if( vm.count(deviceOpt.c_str()) ) {
    std::cout << "Device: " << this->device << std::endl;
  } else {
    throw std::runtime_error("Device not specified");
  }

  if( vm.count(channelOpt.c_str()) ) {
    if( this->channel < 16 ) {
      std::cout << "Channel: " << static_cast<int>(this->channel) << std::endl;
    } else {
      throw std::out_of_range("Channel must be in range 0 to 15");
    }
  } else {
    throw std::runtime_error("Device not specified");
  }
}

