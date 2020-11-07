set(srcs)

list(APPEND srcs mockbop.cpp)
list(APPEND srcs mockbip.cpp)

target_sources(tendril PRIVATE ${srcs})
