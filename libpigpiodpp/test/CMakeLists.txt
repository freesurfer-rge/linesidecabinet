set(srcs test.cpp)

list(APPEND srcs piavailabletests.cpp)
list(APPEND srcs gpiomodetests.cpp)
list(APPEND srcs gpioedgetests.cpp)
list(APPEND srcs gpiopulltests.cpp)
list(APPEND srcs pimanagertests.cpp)
list(APPEND srcs gpiopintests.cpp)
list(APPEND srcs i2cpitests.cpp)
list(APPEND srcs piboparraytests.cpp)

list(APPEND srcs pii2ccommsprovidertests.cpp)
list(APPEND srcs pibopprovidertests.cpp)
list(APPEND srcs piboparrayprovidertests.cpp)
list(APPEND srcs pibipprovidertests.cpp)

list(APPEND srcs pihardwaremanagerfactorytests.cpp)

add_executable(PiGPIOdppTest ${srcs})
target_link_libraries(PiGPIOdppTest PUBLIC pigpiodpp Boost::boost)

add_test(NAME pigpiodpp COMMAND PiGPIOdppTest --log_sink=PiGPIOdppTest-JUNIT.xml ${TEST_COMMON_ARGS})
