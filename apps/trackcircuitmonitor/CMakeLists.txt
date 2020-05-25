set(srcs)

list(APPEND srcs main.cpp)
list(APPEND srcs stubsoftwaremanager.cpp)

add_executable(TrackCircuitMonitor ${srcs})

target_include_directories(TrackCircuitMonitor
  SYSTEM PRIVATE ${Boost_INCLUDE_DIRS})

# Note that linking against the lineside library will
# automatically include the corresponding headers in
# the compile commands
target_link_libraries(TrackCircuitMonitor lineside ${Boost_LIBRARIES})

configure_file(track-circuits.xml . COPYONLY)
