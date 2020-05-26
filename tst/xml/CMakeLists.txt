set(srcs)

list(APPEND srcs xmlutils.cpp)

list(APPEND srcs xercesguardtests.cpp)

list(APPEND srcs settingsreadertests.cpp)
list(APPEND srcs devicerequestdatatests.cpp)
list(APPEND srcs pwitemdatareadertests.cpp)
list(APPEND srcs pwitemlistreadertests.cpp)
list(APPEND srcs softwaremanagerdatareadertests.cpp)
list(APPEND srcs i2cdevicedatareadertests.cpp)
list(APPEND srcs i2cdevicelistreadertests.cpp)
list(APPEND srcs hardwaremanagerdatareadertests.cpp)
list(APPEND srcs configurationreadertests.cpp)

target_sources(LinesideTest PRIVATE ${srcs})
