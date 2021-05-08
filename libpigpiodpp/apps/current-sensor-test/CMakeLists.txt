set(srcs)

list(APPEND srcs main.cpp)

if( pigpio_FOUND )
  add_executable(cstest ${srcs})
  target_include_directories(cstest
    SYSTEM PRIVATE ${pigpio_INCLUDE_DIR})
  target_link_libraries(cstest PUBLIC ${pigpiod_if2_LIBRARY})
else()
  message(STATUS "Unable to build cstest app")
endif()
