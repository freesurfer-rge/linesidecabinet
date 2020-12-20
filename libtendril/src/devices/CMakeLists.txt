set(srcs)

list(APPEND srcs pca9685.cpp)
list(APPEND srcs pca9685channel.cpp)

list(APPEND srcs directdrivesn74x595.cpp)
list(APPEND srcs boparray595.cpp)

list(APPEND srcs factory.cpp)

target_sources(tendril PRIVATE ${srcs})
