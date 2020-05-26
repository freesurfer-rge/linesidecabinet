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
target_include_directories(LinesideTest
  SYSTEM PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(LinesideTest PRIVATE .)
target_link_libraries(LinesideTest lineside ${Boost_LIBRARIES})

add_test(NAME AllTests COMMAND LinesideTest)

add_subdirectory(mocks)

add_subdirectory(pigpiod)

add_subdirectory(xml)
add_subdirectory(xmlsamples)
