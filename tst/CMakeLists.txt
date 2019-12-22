set( srcs test.cpp )

list(APPEND srcs mocks/mockbip.cpp)
list(APPEND srcs mocks/mockhardwaremanager.cpp)

list(APPEND srcs itemidtests.cpp)
list(APPEND srcs exceptiontests.cpp)
list(APPEND srcs registrartests.cpp)
list(APPEND srcs mockbiptests.cpp)
list(APPEND srcs pwitemcontrollertests.cpp)

list(APPEND srcs servoturnoutmotortests.cpp)

add_executable( LinesideTest ${srcs} )
target_include_directories(LinesideTest
  SYSTEM PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(LinesideTest lineside ${Boost_LIBRARIES} )

ADD_TEST(NAME ExampleTest COMMAND LinesideTest)
