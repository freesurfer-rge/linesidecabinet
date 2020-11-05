set(srcs test.cpp)

list(APPEND srcs mockboptests.cpp)

add_executable(TendrilTest ${srcs})
target_link_libraries(TendrilTest PUBLIC tendril Boost::boost)

add_test(NAME tendril
  COMMAND TendrilTest --log_sink=TendrilTest-JUNIT.xml ${TEST_COMMON_ARGS})
