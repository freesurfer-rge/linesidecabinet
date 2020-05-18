set(srcs)

list(APPEND srcs main.cpp)


add_executable(Signals ${srcs})

# Note that linking against the lineside library will
# automatically include the corresponding headers in
# the compile commands
target_link_libraries(Signals lineside)
