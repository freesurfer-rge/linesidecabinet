set(srcs)

list(APPEND srcs xercesguard.cpp)
list(APPEND srcs settingsreader.cpp)
list(APPEND srcs devicerequestdatareader.cpp)
list(APPEND srcs xercesstringdeleter.cpp)
list(APPEND srcs utilities.cpp)
list(APPEND srcs pwitemdatareader.cpp)
list(APPEND srcs servoturnoutmotordatareader.cpp)

target_sources( lineside PRIVATE ${srcs} )
target_include_directories(lineside SYSTEM
  PUBLIC ${XercesC_INCLUDE_DIRS})
target_link_libraries(lineside INTERFACE ${XercesC_LIBRARIES})
