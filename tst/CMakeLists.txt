SET( srcs test.cpp )

LIST(APPEND srcs itemidtests.cpp)

ADD_EXECUTABLE( LinesideTest ${srcs} )

TARGET_LINK_LIBRARIES( LinesideTest lineside ${Boost_LIBRARIES} )

ADD_TEST(NAME ExampleTest COMMAND LinesideTest)
