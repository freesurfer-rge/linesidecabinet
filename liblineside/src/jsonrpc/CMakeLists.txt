set(srcs)

list(APPEND srcs cpphttplibconnector.cpp)

target_sources(lineside PRIVATE ${srcs})

target_include_directories(lineside
  PRIVATE SYSTEM
  ${jsonrpccxx_SOURCE_DIR}/include
  ${cpphttplib_SOURCE_DIR}
)
target_link_libraries(lineside
  PRIVATE
  json-rpc-cxx
  nlohmann_json::nlohmann_json
)
