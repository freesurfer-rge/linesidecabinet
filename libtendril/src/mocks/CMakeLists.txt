set(srcs)

list(APPEND srcs mockbop.cpp)
list(APPEND srcs mockbip.cpp)
list(APPEND srcs mockboparray.cpp)

target_sources(tendril PRIVATE ${srcs})
