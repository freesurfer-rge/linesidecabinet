set(srcs)

list(APPEND srcs mockbop.cpp)
list(APPEND srcs mockbip.cpp)
list(APPEND srcs mockboparray.cpp)
list(APPEND srcs mockpwmchannel.cpp)

target_sources(tendril PRIVATE ${srcs})
