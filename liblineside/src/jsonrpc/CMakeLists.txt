set(srcs)

list(APPEND srcs cpphttplibconnector.cpp)
list(APPEND srcs cabinetservice.cpp)
list(APPEND srcs jsonconvertors.cpp)
list(APPEND srcs rpcserver.cpp)

target_sources(lineside PRIVATE ${srcs})

target_include_directories(lineside SYSTEM
  PUBLIC
  ${jsonrpccxx_SOURCE_DIR}/include
  ${cpphttplib_SOURCE_DIR}
)
target_link_libraries(lineside
  PUBLIC
  nlohmann_json::nlohmann_json
  json-rpc-cxx
)
