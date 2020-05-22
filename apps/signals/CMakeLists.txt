set(srcs)

list(APPEND srcs main.cpp)
list(APPEND srcs cmdlineopts.cpp)
list(APPEND srcs stubsoftwaremanager.cpp)
list(APPEND srcs runonconsole.cpp)

add_executable(Signals ${srcs})

target_include_directories(Signals
  SYSTEM PRIVATE ${Boost_INCLUDE_DIRS})

# Note that linking against the lineside library will
# automatically include the corresponding headers in
# the compile commands
target_link_libraries(Signals lineside ${Boost_LIBRARIES})

configure_file(single-signal.xml . COPYONLY)
