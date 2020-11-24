cmake_minimum_required(VERSION 3.15)
project("Lineside Cabinet"
  VERSION 0.1
  LANGUAGES CXX
  DESCRIPTION "A driver program for lineside equipment for model railways"
  HOMEPAGE_URL https://github.com/freesurfer-rge/linesidecabinet)
enable_testing()

include(FetchContent)

# --------
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(Threads REQUIRED)

# Follow needed on OSX due to DYLD_LIBRARY_PATH issues when running ctest
# set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.65 REQUIRED
  COMPONENTS filesystem program_options)

find_package(Doxygen)

find_package(XercesC REQUIRED)

# --

FetchContent_Declare(jsonrpccxx
  GIT_REPOSITORY https://github.com/jsonrpcx/json-rpc-cxx )

FetchContent_GetProperties(jsonrpccxx)
if(NOT jsoncprcxx_POPULATED)
  FetchContent_Populate(jsonrpccxx)
  add_subdirectory(${jsonrpccxx_SOURCE_DIR} ${jsonrpccxx_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# --

FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.9.1)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# --

FetchContent_Declare(cpphttplib
  GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git)

FetchContent_GetProperties(cpphttplib)
if(NOT cpphttplib_POPULATED)
  FetchContent_Populate(cpphttplib)
  add_subdirectory(${cpphttplib_SOURCE_DIR} ${cpphttplib_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


# --------

# Configure the language standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Warning options for the compiler
string(
  APPEND _warning_opts
  "$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Wall;-Wextra;-Weffc++;-Werror;>"
  "$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:-Wthread-safety;-Wpedantic;>"
  "$<$<CXX_COMPILER_ID:GNU>:-pedantic;-pedantic-errors;>"
  )

add_compile_options("${_warning_opts}")

# Profiling options (GCC only for now)
string(
  APPEND _profile_opts
  "$<$<AND:$<CXX_COMPILER_ID:GNU>,$<CONFIG:DEBUG>>:--coverage;>"
  )
add_compile_options("${_profile_opts}")
add_link_options("${_profile_opts}")

# --------

# Set up testing settings

set(TEST_COMMON_ARGS --log_level=all --log_format=JUNIT --report_sink=stdout)

# --------

add_subdirectory( libtendril )
add_subdirectory( libpigpiodpp )
add_subdirectory( liblineside )
# add_subdirectory( apps ) PENDING LIBTENDRIL CONVERSION

# --------

if(DOXYGEN_FOUND)
  set(DOXYGEN_OUTPUT_DIRECTORY docs)
  doxygen_add_docs(docs
    COMMENT "Generating API documentation with Doxygen")
else(DOXYGEN_FOUND)
  message("Doxygen not found. Will not be able to build documentation")
endif(DOXYGEN_FOUND)
      
