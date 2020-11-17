# Declare the library target
add_library(lineside)

# Set up the includes so that it works
# - When building from source
# - When installed (should that ever happen)
target_include_directories(lineside
  PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Setup the linking
target_link_libraries(lineside
  PUBLIC tendril
  PUBLIC Threads::Threads
  PRIVATE Boost::boost)

add_subdirectory(src)
add_subdirectory(test)
