set(srcs)

list(APPEND srcs xercesguard.cpp)
list(APPEND srcs xercesstringdeleter.cpp)
list(APPEND srcs utilities.cpp)

list(APPEND srcs settingsreader.cpp)
list(APPEND srcs hardwarerequestdatareader.cpp)

list(APPEND srcs devicedatareader.cpp)
list(APPEND srcs directdrivesn74x595datareader.cpp)
list(APPEND srcs devicelistreader.cpp)

list(APPEND srcs pwitemdatareader.cpp)
list(APPEND srcs servoturnoutmotordatareader.cpp)
list(APPEND srcs trackcircuitmonitordatareader.cpp)
list(APPEND srcs directdrivemashdatareader.cpp)
list(APPEND srcs boparraymashdatareader.cpp)
list(APPEND srcs pwitemlistreader.cpp)

list(APPEND srcs softwaremanagerdatareader.cpp)
list(APPEND srcs hardwaremanagerdatareader.cpp)

list(APPEND srcs configurationreader.cpp)

target_sources( lineside PRIVATE ${srcs} )
target_include_directories(lineside SYSTEM
  PUBLIC ${XercesC_INCLUDE_DIRS})
target_link_libraries(lineside INTERFACE ${XercesC_LIBRARIES})
