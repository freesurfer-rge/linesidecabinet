#include <iostream>

#include <pigpiod_if2.h>

int main(int argc, char* argv[]) {
  std::cout << "Current Sensor Test" << std::endl;

  if( argc != 2 ) {
    std::cerr << "Must specify two times" << std::endl;
    return 1;
  }

  const unsigned int onTime = atoi(argv[1]);
  const unsigned int offTime = atoi(argv[2]);

  std::cout << "onTime " << onTime << " us" << std::endl;
  std::cout << "offTime " << offTime << " us" << std::endl;
  
  const int piId = pigpio_start(nullptr, nullptr);
  if( piId< 0 ) {
    std::cerr << "Could not connect to pigpiod."
              << "Have you run 'sudo pigpiod' ?"
              << std::endl;
    return(-1);
  }
  
  pigpio_stop(piId);
  
  return 0;
}
