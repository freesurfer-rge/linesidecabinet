set(srcs)

list(APPEND srcs main.cpp)
list(APPEND srcs cmdlineopts.cpp)
list(APPEND srcs stubsoftwaremanager.cpp)

add_executable(LinesideCabinet ${srcs})

target_link_libraries(LinesideCabinet PUBLIC lineside Boost::program_options)

configure_file(sample-configuration.xml . COPYONLY)
