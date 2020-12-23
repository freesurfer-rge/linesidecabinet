set(srcs)

list(APPEND srcs i2cdevicedatatests.cpp)

list(APPEND srcs pca9685tests.cpp)

list(APPEND srcs directdrivesn74x595datatests.cpp)
list(APPEND srcs directdrivesn74x595tests.cpp)

target_sources(TendrilTest PRIVATE ${srcs})
