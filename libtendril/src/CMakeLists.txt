set(srcs)

list(APPEND srcs binaryinputpin.cpp)
list(APPEND srcs boparray.cpp)

target_sources(tendril PRIVATE ${srcs})

add_subdirectory(mocks)
