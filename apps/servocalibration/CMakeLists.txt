set(srcs)

list(APPEND srcs main.cpp)
list(APPEND srcs cmdlineopts.cpp)
list(APPEND srcs runonconsole.cpp)

add_executable(ServoCalibration ${srcs})

# Note that linking against the lineside library will
# automatically include the corresponding headers in
# the compile commands
target_link_libraries(ServoCalibration PUBLIC lineside Boost::program_options)

configure_file(single-device.xml . COPYONLY)
