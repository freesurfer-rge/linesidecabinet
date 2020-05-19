#include <cstdlib>
#include <iostream>

#include "xml/configurationreader.hpp"
#include "multiaspectsignalheaddata.hpp"

#include "cmdlineopts.hpp"


void CheckPWItems(const std::vector<std::shared_ptr<Lineside::PWItemData>>& pwItems) {
  for( auto it=pwItems.begin(); it!=pwItems.end(); ++it ) {
    auto signal = std::dynamic_pointer_cast<Lineside::MultiAspectSignalHeadData>(*it);
    if( !signal ) {
      throw std::runtime_error("All PWItems must be of type MultiAspectSignalHead");
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

  }
  catch(std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
