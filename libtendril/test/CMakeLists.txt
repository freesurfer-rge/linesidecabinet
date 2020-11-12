set(srcs test.cpp)

list(APPEND srcs keyexceptiontests.cpp)

list(APPEND srcs boparraytests.cpp)

list(APPEND srcs mockboptests.cpp)
list(APPEND srcs mocknotifiabletests.cpp)
list(APPEND srcs notifiertests.cpp)
list(APPEND srcs mockbiptests.cpp)
list(APPEND srcs mockboparraytests.cpp)
list(APPEND srcs mockpwmchanneltests.cpp)

list(APPEND srcs mocki2ccommunicatortests.cpp)

list(APPEND srcs registrartests.cpp)

list(APPEND srcs mockhardwareprovidertests.cpp)
list(APPEND srcs mockboparrayprovidertests.cpp)
list(APPEND srcs mockhardwaremanagertests.cpp)

list(APPEND srcs pca9685tests.cpp)

add_executable(TendrilTest ${srcs})
target_link_libraries(TendrilTest PUBLIC tendril Boost::boost)

add_test(NAME tendril
  COMMAND TendrilTest --log_sink=TendrilTest-JUNIT.xml ${TEST_COMMON_ARGS})
