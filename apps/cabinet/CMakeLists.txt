set(srcs)

list(APPEND srcs main.cpp)

add_executable(LinesideCabinet ${srcs})

target_link_libraries(LinesideCabinet PUBLIC lineside)
