set(srcs)

list(APPEND srcs main.cpp)

add_executable(led8x8 ${srcs})
target_include_directories(led8x8
    SYSTEM PRIVATE ${pigpio_INCLUDE_DIR})
target_link_libraries(led8x8 PUBLIC ${pigpiod_if2_LIBRARY})
