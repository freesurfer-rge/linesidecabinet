cmake_minimum_required(VERSION 3.15)
project("Lineside Cabinet"
  VERSION 0.1
  LANGUAGES CXX
  DESCRIPTION "A driver program for lineside equipment for model railways"
  HOMEPAGE_URL https://github.com/freesurfer-rge/linesidecabinet)
enable_testing()

# --------
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(Threads REQUIRED)

# Follow needed on OSX due to DYLD_LIBRARY_PATH issues when running ctest
# set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.71 REQUIRED
  COMPONENTS filesystem program_options)

find_package(Doxygen)

find_package(XercesC REQUIRED)

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
add_subdirectory( apps )

# --------

if(DOXYGEN_FOUND)
  set(DOXYGEN_OUTPUT_DIRECTORY docs)
  doxygen_add_docs(docs
    COMMENT "Generating API documentation with Doxygen")
else(DOXYGEN_FOUND)
  message("Doxygen not found. Will not be able to build documentation")
endif(DOXYGEN_FOUND)
      
