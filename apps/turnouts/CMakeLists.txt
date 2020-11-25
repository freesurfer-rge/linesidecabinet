set(srcs)

list(APPEND srcs main.cpp)
list(APPEND srcs cmdlineopts.cpp)
list(APPEND srcs stubsoftwaremanager.cpp)
list(APPEND srcs runonconsole.cpp)

add_executable(Turnouts ${srcs})

# Note that linking against the lineside library will
# automatically include the corresponding headers in
# the compile commands
target_link_libraries(Turnouts PUBLIC lineside pigpiodpp Boost::program_options)

configure_file(two-turnout.xml . COPYONLY)
