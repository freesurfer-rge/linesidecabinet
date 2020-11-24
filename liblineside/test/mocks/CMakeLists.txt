set(srcs)

list(APPEND srcs mockrtcclient.cpp)
list(APPEND srcs mocksoftwaremanager.cpp)

target_sources(LinesideTest PRIVATE ${srcs} )
