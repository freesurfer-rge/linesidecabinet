set(srcs test.cpp)

list(APPEND srcs mockbiptests.cpp)
list(APPEND srcs mockbipprovidertests.cpp)
list(APPEND srcs mockbopprovidertests.cpp)
list(APPEND srcs mockpwmchanneltests.cpp)
list(APPEND srcs mockpwmchannelprovidertests.cpp)

list(APPEND srcs turnoutstatetests.cpp)
list(APPEND srcs signalstatetests.cpp)
list(APPEND srcs signalaspecttests.cpp)
list(APPEND srcs signalflashtests.cpp)

list(APPEND srcs itemidtests.cpp)
list(APPEND srcs exceptiontests.cpp)
list(APPEND srcs utilitytests.cpp)
list(APPEND srcs registrartests.cpp)
list(APPEND srcs pwitemcontrollertests.cpp)

list(APPEND srcs multiaspectsignalheaddatatests.cpp)
list(APPEND srcs multiaspectsignalheadtests.cpp)

list(APPEND srcs servoturnoutmotortests.cpp)

list(APPEND srcs trackcircuitmonitortests.cpp)

list(APPEND srcs pwitemmanagertests.cpp)


add_executable(LinesideTest ${srcs})
# The following is so that subdirectories can find things like
# exceptionmessagecheck.hpp
target_include_directories(LinesideTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(LinesideTest PUBLIC lineside Boost::unit_test_framework)

add_test(NAME Quick COMMAND LinesideTest --run_test=\!@LongRunning)

add_subdirectory(mocks)

add_subdirectory(pigpiod)

add_subdirectory(xml)
add_subdirectory(xmlsamples)
