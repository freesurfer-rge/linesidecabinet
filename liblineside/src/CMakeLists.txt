set(srcs)

list(APPEND srcs turnoutstate.cpp)
list(APPEND srcs signalstate.cpp)
list(APPEND srcs signalaspect.cpp)
list(APPEND srcs signalflash.cpp)
list(APPEND srcs trackcircuitsensor.cpp)

list(APPEND srcs itemid.cpp)
list(APPEND srcs pwitemmodel.cpp)
list(APPEND srcs pwitemcontroller.cpp)

list(APPEND srcs pwitemdata.cpp)

list(APPEND srcs servoturnoutmotordata.cpp)
list(APPEND srcs servoturnoutmotor.cpp)

list(APPEND srcs trackcircuitmonitordata.cpp)
list(APPEND srcs trackcircuitmonitor.cpp)

list(APPEND srcs directdrivemashdata.cpp)
list(APPEND srcs directdrivemash.cpp)

list(APPEND srcs pwitemmanager.cpp)

# -- 

target_sources(lineside PRIVATE ${srcs})

add_subdirectory(xml)
add_subdirectory(jsonrpc)
