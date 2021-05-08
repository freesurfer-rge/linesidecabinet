#include <chrono>
#include <iostream>
#include <thread>

#include <pigpiod_if2.h>

int main(int argc, char* argv[]) {
  std::cout << "Current Sensor Test" << std::endl;

  if( argc != 4 ) {
    std::cerr << "Must specify two times and a pin" << std::endl;
    return 1;
  }

  const unsigned int onTime = atoi(argv[1]);
  const unsigned int offTime = atoi(argv[2]);
  const unsigned int pin = atoi(argv[3]);

  std::cout << "onTime " << onTime << " us" << std::endl;
  std::cout << "offTime " << offTime << " us" << std::endl;

  const std::chrono::microseconds onus{onTime};
  const std::chrono::microseconds offus{offTime};
  
  const int piId = pigpio_start(nullptr, nullptr);
  if( piId < 0 ) {
    std::cerr << "Could not connect to pigpiod."
              << "Have you run 'sudo pigpiod' ?"
              << std::endl;
    return(-1);
  }

  set_mode(piId, pin, PI_OUTPUT);
  while(true) {
    gpio_write(piId, pin, 1);
    std::this_thread::sleep_for(onus);
    gpio_write(piId, pin, 0);
    std::this_thread::sleep_for(offus);
  }
  
  pigpio_stop(piId);
  
  return 0;
}
