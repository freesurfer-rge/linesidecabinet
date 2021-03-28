set(srcs)

list(APPEND srcs main.cpp)
list(APPEND srcs cmdlineopts.cpp)

add_executable(led8x8 ${srcs})
target_link_libraries(led8x8 PUBLIC pigpiodpp Boost::program_options)
