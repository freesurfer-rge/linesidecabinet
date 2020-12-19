set(srcs)

list(APPEND srcs xmlutils.cpp)

list(APPEND srcs configurationreadertests.cpp)
list(APPEND srcs hardwarerequestdatareadertests.cpp)
list(APPEND srcs hardwaremanagerdatareadertests.cpp)
list(APPEND srcs i2cdevicedatareadertests.cpp)
list(APPEND srcs i2cdevicelistreadertests.cpp)
list(APPEND srcs pwitemdatareadertests.cpp)
list(APPEND srcs pwitemlistreadertests.cpp)
list(APPEND srcs settingsreadertests.cpp)
list(APPEND srcs softwaremanagerdatareadertests.cpp)
list(APPEND srcs xercesguardtests.cpp)

target_sources(LinesideTest PRIVATE ${srcs})
target_link_libraries(LinesideTest PUBLIC Boost::filesystem)
