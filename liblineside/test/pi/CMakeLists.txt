set(srcs)

list(APPEND srcs gpinputprovidertests.cpp)
list(APPEND srcs gpioprovidertests.cpp)
list(APPEND srcs gpoutputprovidertests.cpp)
list(APPEND srcs pihardwaremanagertests.cpp)

target_sources(LinesideTest PRIVATE ${srcs})
