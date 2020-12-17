# Declare the library target
add_library(pigpiodpp)

find_package(pigpio)

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
  PUBLIC tendril
  PUBLIC Threads::Threads
  PRIVATE Boost::boost)

# Process the piAvailable header
configure_file( "${CMAKE_CURRENT_SOURCE_DIR}/include/pigpiodpp/piavailable.hpp.in"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/pigpiodpp/piavailable.hpp" )
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(apps)
