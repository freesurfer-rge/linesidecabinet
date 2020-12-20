set(srcs)

list(APPEND srcs binaryinputpin.cpp)
list(APPEND srcs boparray.cpp)

list(APPEND srcs hardwaremanager.cpp)

target_sources(tendril PRIVATE ${srcs})

add_subdirectory(devices)
add_subdirectory(mocks)
