set( srcs )

list(APPEND srcs itemid.cpp)

add_library( lineside ${srcs} )
target_include_directories(lineside
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  SYSTEM PRIVATE ${Boost_INCLUDE_DIRS})
