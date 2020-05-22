set(srcs)

list(APPEND srcs turnoutstate.cpp)
list(APPEND srcs signalstate.cpp)
list(APPEND srcs signalaspect.cpp)
list(APPEND srcs signalflash.cpp)

list(APPEND srcs itemid.cpp)
list(APPEND srcs binaryinputpin.cpp)
list(APPEND srcs pwitemmodel.cpp)
list(APPEND srcs pwitemcontroller.cpp)

list(APPEND srcs pwitemdata.cpp)

list(APPEND srcs servoturnoutmotordata.cpp)
list(APPEND srcs servoturnoutmotor.cpp)

list(APPEND srcs trackcircuitmonitordata.cpp)
list(APPEND srcs trackcircuitmonitor.cpp)

list(APPEND srcs multiaspectsignalheaddata.cpp)
list(APPEND srcs multiaspectsignalhead.cpp)

list(APPEND srcs pwitemmanager.cpp)

add_library(lineside ${srcs})
target_include_directories(lineside
  PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(lineside SYSTEM
  PRIVATE ${Boost_INCLUDE_DIRS})

add_subdirectory(xml)
add_subdirectory(pigpiod)
