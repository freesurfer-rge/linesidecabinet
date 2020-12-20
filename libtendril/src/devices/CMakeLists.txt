set(srcs)

list(APPEND srcs i2cdevicedata.cpp)

list(APPEND srcs pca9685.cpp)
list(APPEND srcs pca9685channel.cpp)

list(APPEND srcs directdrivesn74x595data.cpp)
list(APPEND srcs directdrivesn74x595.cpp)
list(APPEND srcs boparray595.cpp)

target_sources(tendril PRIVATE ${srcs})
