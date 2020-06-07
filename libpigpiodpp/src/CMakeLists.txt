find_package(pigpio)

add_library(pigpiodpp)

set(srcs)

list(APPEND srcs gpiopull.cpp)

if( pigpio_FOUND )
  target_add_compile_definitions(pigpiodpp "HAVE_PIGPIO")
  target_include_directories(pigpiodpp
    SYSTEM PRIVATE ${pigpio_INCLUDE_DIR})
  target_link_libraries(pigpiodpp PRIVATE ${pigpiod_if2_LIBRARY)
else()
  target_include_directories(pigpiodpp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
  list(APPEND srcs pigpiodstubs.cpp)
endif()

target_sources(pigpiodpp PRIVATE ${srcs})
target_include_directories(pigpiodpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include/)
target_link_libraries(pigpiodpp PRIVATE Boost::boost)
