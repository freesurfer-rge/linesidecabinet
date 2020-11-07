set(srcs)

list(APPEND srcs binaryinputpin.cpp)

target_sources(tendril PRIVATE ${srcs})

add_subdirectory(mocks)
