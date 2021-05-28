# Note that headers are optional, and do not affect add_library,
# but they will not show up in IDEs unless they are listed in add_library.

# Add header files
file(GLOB HEADERS_LIST CONFIGURE_DEPENDS
     "${PROJECT_SOURCE_DIR}/include/sdlxx/image/*.h")

# Add source files
set(SOURCES_LIST
    image_surface.cpp
    image_texture.cpp
    image_api.cpp)

# Make an automatic library - will be static or dynamic based on user setting
add_library(sdlxx_image ${HEADERS_LIST} ${SOURCES_LIST})
add_library(sdlxx::image ALIAS sdlxx_image)
add_library(SDLXX::Image ALIAS sdlxx_image)

# Set include directory and make it visible to users
target_include_directories(sdlxx_image PUBLIC "${PROJECT_SOURCE_DIR}/include")

# Add dependencies
find_package(sdl2-image CONFIG REQUIRED)
target_link_libraries(sdlxx_image PUBLIC
                      sdlxx_core
                      SDL2::SDL2_image)

# Set C++ standard to C++17
target_compile_features(sdlxx_image PRIVATE cxx_std_17)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include"
             PREFIX "Header Files"
             FILES ${HEADERS_LIST})
