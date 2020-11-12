# Declare the library target
add_library(tendril)

# Set up the includes so that it works
# - When building from source
# - When installed (should that ever happen)
target_include_directories(tendril
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)


add_subdirectory(src)
add_subdirectory(test)
