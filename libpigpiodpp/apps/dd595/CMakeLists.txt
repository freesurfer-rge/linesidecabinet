set(srcs)

list(APPEND srcs main.cpp)
list(APPEND srcs cmdlineopts.cpp)
list(APPEND srcs runonconsole.cpp)

add_executable(dd595 ${srcs})
target_link_libraries(dd595 PUBLIC pigpiodpp Boost::program_options)
