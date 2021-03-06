set(srcs test.cpp)

list(APPEND srcs turnoutstatetests.cpp)
list(APPEND srcs signalstatetests.cpp)
list(APPEND srcs signalaspecttests.cpp)
list(APPEND srcs signalflashtests.cpp)
list(APPEND srcs trackcircuitsensortests.cpp)

list(APPEND srcs itemidtests.cpp)
list(APPEND srcs exceptiontests.cpp)
list(APPEND srcs pwitemcontrollertests.cpp)

list(APPEND srcs directdrivemashdatatests.cpp)
list(APPEND srcs directdrivemashtests.cpp)
list(APPEND srcs boparraymashdatatests.cpp)
list(APPEND srcs boparraymashtests.cpp)

list(APPEND srcs servoturnoutmotortests.cpp)

list(APPEND srcs trackcircuitmonitortests.cpp)

list(APPEND srcs pwitemmanagertests.cpp)


add_executable(LinesideTest ${srcs})
# The following is so that subdirectories can find things like
# exceptionmessagecheck.hpp
target_include_directories(LinesideTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(LinesideTest PUBLIC lineside Boost::boost Boost::filesystem)

#  To inhibit the longer running tests, add
# --run_test=\!@LongRunning
# to the command
add_test(NAME lineside COMMAND LinesideTest --log_sink=LinesideTest-JUNIT.xml ${TEST_COMMON_ARGS})

add_subdirectory(mocks)
add_subdirectory(xml)
add_subdirectory(xmlsamples)
