set(srcs)

list(APPEND srcs main.cpp)
list(APPEND srcs stubsoftwaremanager.cpp)
list(APPEND srcs cmdlineopts.cpp)

add_executable(TrackCircuitMonitor ${srcs})

# Note that linking against the lineside library will
# automatically include the corresponding headers in
# the compile commands
target_link_libraries(TrackCircuitMonitor PUBLIC lineside Boost::program_options)

configure_file(track-circuits.xml . COPYONLY)
