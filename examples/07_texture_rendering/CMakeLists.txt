# Note that headers are optional, and do not affect add_library,
# but they will not show up in IDEs unless they are listed in add_library.

# Add header files
set(HEADERS_LIST "")

# Add source files
set(SOURCES_LIST main.cpp)

# Make an executable
add_executable(texture_rendering ${HEADERS_LIST} ${SOURCES_LIST})

# Add dependencies
target_link_libraries(texture_rendering PRIVATE sdlxx::core sdlxx::image)

# Set C++ standard to C++17
target_compile_features(texture_rendering PRIVATE cxx_std_17)

# Copy assets
file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# IDEs should put the headers in a nice place
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
             PREFIX "Header Files"
             FILES ${HEADERS_LIST})
