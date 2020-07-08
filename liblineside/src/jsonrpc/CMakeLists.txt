set(srcs)

list(APPEND srcs cpphttplibconnector.cpp)
list(APPEND srcs cabinetserver.cpp)
list(APPEND srcs jsonconvertors.cpp)

target_sources(lineside PRIVATE ${srcs})

target_include_directories(lineside SYSTEM
  PRIVATE
  ${jsonrpccxx_SOURCE_DIR}/include
  ${cpphttplib_SOURCE_DIR}
)
target_link_libraries(lineside
  PUBLIC
  nlohmann_json::nlohmann_json
  PRIVATE
  json-rpc-cxx
)
