set(srcs test.cpp)

list(APPEND srcs gpiopulltests.cpp)
list(APPEND srcs pimanagertests.cpp)
list(APPEND srcs gpiopintests.cpp)


add_executable(PiGPIOdppTest ${srcs})
target_link_libraries(PiGPIOdppTest PUBLIC pigpiodpp Boost::boost)

add_test(NAME pigpiodpp COMMAND PiGPIOdppTest --log_sink=${TEST_RESULTS_DIRECTORY}/PiGPIOdppTest-JUNIT.xml ${TEST_COMMON_ARGS})
