set(srcs)

list(APPEND srcs mockbip.cpp)
list(APPEND srcs mockpwmchannel.cpp)
list(APPEND srcs mockpwmchannelprovider.cpp)
list(APPEND srcs mockbopprovider.cpp)
list(APPEND srcs mockbipprovider.cpp)
list(APPEND srcs mockhardwaremanager.cpp)
list(APPEND srcs mockrtcclient.cpp)
list(APPEND srcs mocksoftwaremanager.cpp)

target_sources(LinesideTest PRIVATE ${srcs} )
