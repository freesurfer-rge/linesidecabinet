set(srcs)

list(APPEND srcs xercesguard.cpp)
list(APPEND srcs settingsreader.cpp)
list(APPEND srcs devicerequestdatareader.cpp)
list(APPEND srcs xercesstringdeleter.cpp)
list(APPEND srcs utilities.cpp)
list(APPEND srcs pwitemdatareader.cpp)
list(APPEND srcs servoturnoutmotordatareader.cpp)
list(APPEND srcs trackcircuitmonitordatareader.cpp)
list(APPEND srcs multiaspectsignalheaddatareader.cpp)
list(APPEND srcs pwitemlistreader.cpp)

target_sources( lineside PRIVATE ${srcs} )
target_include_directories(lineside SYSTEM
  PUBLIC ${XercesC_INCLUDE_DIRS})
target_link_libraries(lineside INTERFACE ${XercesC_LIBRARIES})
