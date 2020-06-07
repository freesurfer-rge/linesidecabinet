set(srcs)

list(APPEND srcs main.cpp)
list(APPEND srcs cmdlineopts.cpp)
list(APPEND srcs stubsoftwaremanager.cpp)
list(APPEND srcs runonconsole.cpp)

add_executable(Signals ${srcs})

# Note that linking against the lineside library will
# automatically include the corresponding headers in
# the compile commands
target_link_libraries(Signals PUBLIC lineside Boost::program_options)

configure_file(single-signal.xml . COPYONLY)
