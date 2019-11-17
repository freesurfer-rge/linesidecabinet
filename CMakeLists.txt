CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(LinesideCabinet)
ENABLE_TESTING()

set(Boost_USE_STATIC_LIBS ON)
FIND_PACKAGE(Boost REQUIRED COMPONENTS filesystem system program_options)
INCLUDE_DIRECTORIES(SYSTEM ${Boost_INCLUDE_DIRS})

FIND_PACKAGE(Doxygen
             REQUIRED dot)

SET(doxyfile_in ${PROJECT_SOURCE_DIR}/Doxyfile.in)
SET(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

CONFIGURE_FILE(${doxyfile_in} ${doxyfile} @ONLY)

# Sort out compiler flags
IF(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  SET(PLATFORM_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wthread-safety -Wpedantic -Wc++11-compat-pedantic -Weffc++")
ELSEIF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  SET(PLATFORM_CXX_FLAGS "-std=c++11 -pthread -Wall -Wextra -Weffc++ -pedantic")
ENDIF()

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g ${PLATFORM_CXX_FLAGS}")

INCLUDE_DIRECTORIES( ./include )

ADD_SUBDIRECTORY( src )
ADD_SUBDIRECTORY( tst )

ADD_CUSTOM_TARGET( docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
