cmake_minimum_required(VERSION 3.12)
project(LinesideCabinet
  VERSION 0.1
  LANGUAGES CXX)
ENABLE_TESTING()

set(Boost_USE_STATIC_LIBS ON)
FIND_PACKAGE(Boost REQUIRED)
INCLUDE_DIRECTORIES(SYSTEM ${Boost_INCLUDE_DIRS})

FIND_PACKAGE(Doxygen
             REQUIRED dot)

SET(doxyfile_in ${PROJECT_SOURCE_DIR}/Doxyfile.in)
SET(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

CONFIGURE_FILE(${doxyfile_in} ${doxyfile} @ONLY)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Sort out compiler flags
#IF(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#  SET(PLATFORM_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wthread-safety -Wpedantic -Wc++11-compat-pedantic -Weffc++")
#ELSEIF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
#  SET(PLATFORM_CXX_FLAGS "-std=c++11 -pthread -Wall -Wextra -Weffc++ -pedantic")
#ENDIF()

#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g ${PLATFORM_CXX_FLAGS}")

INCLUDE_DIRECTORIES( ./include )

ADD_SUBDIRECTORY( src )
ADD_SUBDIRECTORY( tst )

ADD_CUSTOM_TARGET( docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
