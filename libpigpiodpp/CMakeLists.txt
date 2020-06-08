# Declare the library target
add_library(pigpiodpp)

# Set up the includes so that it works
# - When building from source
# - When installed (should that ever happen)
target_include_directories(pigpiodpp
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Setup the linking
target_link_libraries(pigpiodpp
  PUBLIC Threads::Threads
  PRIVATE Boost::boost)

add_subdirectory(src)
add_subdirectory(test)
