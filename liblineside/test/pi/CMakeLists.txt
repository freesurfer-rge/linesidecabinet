set(srcs)

list(APPEND srcs gpinputprovidertests.cpp)
list(APPEND srcs gpioprovidertests.cpp)
list(APPEND srcs gpoutputprovidertests.cpp)
list(APPEND srcs pihardwaremanagertests.cpp)
list(APPEND srcs pca9685tests.cpp)

target_sources(LinesideTest PRIVATE ${srcs})
