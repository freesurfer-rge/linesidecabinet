set(srcs)

list(APPEND srcs gpoutput.cpp)
list(APPEND srcs gpinput.cpp)
list(APPEND srcs gpioprovider.cpp)
list(APPEND srcs gpoutputprovider.cpp)
list(APPEND srcs gpinputprovider.cpp)

list(APPEND srcs pihardwaremanager.cpp)

target_sources( lineside PRIVATE ${srcs} )
target_link_libraries(lineside PRIVATE pigpiodpp)

