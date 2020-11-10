set(srcs)

list(APPEND srcs mockbop.cpp)
list(APPEND srcs mockbip.cpp)
list(APPEND srcs mockboparray.cpp)
list(APPEND srcs mockpwmchannel.cpp)

list(APPEND srcs mocki2ccommunicator.cpp)

list(APPEND srcs mockbopprovider.cpp)

target_sources(tendril PRIVATE ${srcs})
