set(srcs)

list(APPEND srcs pca9685.cpp)
list(APPEND srcs pca9685channel.cpp)

target_sources(tendril PRIVATE ${srcs})
