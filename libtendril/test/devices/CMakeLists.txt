set(srcs)

list(APPEND srcs i2cdevicedatatests.cpp)

target_sources(TendrilTest PRIVATE ${srcs})
