find_package(pigpio)

add_library(pigpiodpp)

set(srcs)

list(APPEND srcs gpiopull.cpp)
list(APPEND srcs gpiopin.cpp)
list(APPEND srcs pimanager.cpp)

if( pigpio_FOUND )
  target_compile_definitions(pigpiodpp PRIVATE "HAVE_PIGPIO")
  target_include_directories(pigpiodpp
    SYSTEM PRIVATE ${pigpio_INCLUDE_DIR})
  target_link_libraries(pigpiodpp PRIVATE ${pigpiod_if2_LIBRARY})
else()
  list(APPEND srcs pigpiodstubs.cpp)
endif()

target_sources(pigpiodpp PRIVATE ${srcs})
target_include_directories(pigpiodpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include/)
target_link_libraries(pigpiodpp PRIVATE Boost::boost)
