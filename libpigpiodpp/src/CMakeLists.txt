find_package(pigpio)

set(srcs)

list(APPEND srcs gpiopull.cpp)
list(APPEND srcs gpiopin.cpp)
list(APPEND srcs pimanager.cpp)

# Have to do different things if we find the C pigpiod library
if( pigpio_FOUND )
  target_compile_definitions(pigpiodpp PUBLIC "PIGPIODPP_HAVE_PIGPIO")
  target_include_directories(pigpiodpp
    SYSTEM PRIVATE ${pigpio_INCLUDE_DIR})
  target_link_libraries(pigpiodpp PRIVATE ${pigpiod_if2_LIBRARY})
else()
  message(STATUS "Using stubs in place of pigpiod")
  list(APPEND srcs pigpiodstubs.cpp)
endif()

target_sources(pigpiodpp PRIVATE ${srcs})
