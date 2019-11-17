cmake_minimum_required(VERSION 3.12)
project(LinesideCabinet
  VERSION 0.1
  LANGUAGES CXX)
ENABLE_TESTING()

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED)
INCLUDE_DIRECTORIES(SYSTEM ${Boost_INCLUDE_DIRS})

FIND_PACKAGE(Doxygen
             REQUIRED dot)

SET(doxyfile_in ${PROJECT_SOURCE_DIR}/Doxyfile.in)
SET(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

CONFIGURE_FILE(${doxyfile_in} ${doxyfile} @ONLY)


# Configure the language standard
set(CMAKE_CXX_STANDARD 11)
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

# Threading options for the compiler
string(
  APPEND _thread_opts
  "$<$<CXX_COMPILER_ID:GNU>:-pthread;>"
  )
add_compile_options("${_thread_opts}")


INCLUDE_DIRECTORIES( ./include )

add_subdirectory( src )
add_subdirectory( tst )

ADD_CUSTOM_TARGET( docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
