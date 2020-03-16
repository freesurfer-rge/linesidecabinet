set( srcs )

list(APPEND srcs xercesguard.cpp)

target_sources( lineside PRIVATE ${srcs} )
target_include_directories(lineside SYSTEM
  PRIVATE ${XercesC_INCLUDE_DIRS})
