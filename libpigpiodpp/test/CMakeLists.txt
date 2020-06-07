set(srcs test.cpp)

list(APPEND srcs gpiopulltests.cpp)


add_executable(PiGPIOdppTest ${srcs})
target_link_libraries(PiGPIOdppTest PUBLIC pigpiodpp Boost::boost)

add_test(NAME pigpiodpp COMMAND PiGPIOdppTest)
