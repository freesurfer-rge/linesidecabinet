set(srcs test.cpp)

list(APPEND srcs mockbiptests.cpp)
list(APPEND srcs mockpwmchanneltests.cpp)
list(APPEND srcs mockpwmchannelprovidertests.cpp)
list(APPEND srcs mockbopprovidertests.cpp)
list(APPEND srcs mockbipprovidertests.cpp)

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

list(APPEND srcs xmlutils.cpp)
list(APPEND srcs xercesguardtests.cpp)
list(APPEND srcs settingsreadertests.cpp)
list(APPEND srcs devicerequestdatatests.cpp)
list(APPEND srcs pwitemdatareadertests.cpp)
list(APPEND srcs pwitemlistreadertests.cpp)
list(APPEND srcs softwaremanagerdatareadertests.cpp)
list(APPEND srcs i2cdevicedatareadertests.cpp)
list(APPEND srcs i2cdevicelistreadertests.cpp)
list(APPEND srcs hardwaremanagerdatareadertests.cpp)
list(APPEND srcs configurationreadertests.cpp)

list(APPEND srcs pwitemmanagertests.cpp)

list(APPEND srcs pimanagertests.cpp)
list(APPEND srcs gpiopintests.cpp)
list(APPEND srcs gpioprovidertests.cpp)
list(APPEND srcs gpoutputprovidertests.cpp)
list(APPEND srcs pihardwaremanagertests.cpp)

add_executable(LinesideTest ${srcs})
target_include_directories(LinesideTest
  SYSTEM PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(LinesideTest lineside ${Boost_LIBRARIES})

add_test(NAME AllTests COMMAND LinesideTest)

add_subdirectory(mocks)


add_subdirectory(xmlsamples)
