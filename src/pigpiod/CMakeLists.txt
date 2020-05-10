set(srcs)

if( NOT pigpio_FOUND )
  list(APPEND srcs pigpiodstubs.cpp)
endif()

list(APPEND srcs pimanager.cpp)
list(APPEND srcs gpiopin.cpp)

target_sources( lineside PRIVATE ${srcs} )

if( pigpio_FOUND )
  target_include_directories(lineside SYSTEM
    PRIVATE ${pigpio_INCLUDE_DIR})
  target_link_libraries(lineside PRIVATE ${pigpiod_if2_LIBRARY})
endif()
