set( srcs )

list(APPEND srcs itemid.cpp)
list(APPEND srcs binaryinputpin.cpp)

add_library( lineside ${srcs} )
target_include_directories(lineside
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  SYSTEM PRIVATE ${Boost_INCLUDE_DIRS})
