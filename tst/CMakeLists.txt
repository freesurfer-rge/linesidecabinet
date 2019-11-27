set( srcs test.cpp )

list(APPEND srcs itemidtests.cpp)
list(APPEND srcs registrartests.cpp)

add_executable( LinesideTest ${srcs} )
target_include_directories(LinesideTest
  SYSTEM PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(LinesideTest lineside ${Boost_LIBRARIES} )

ADD_TEST(NAME ExampleTest COMMAND LinesideTest)
