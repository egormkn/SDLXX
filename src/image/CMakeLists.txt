# Note that headers are optional, and do not affect add_library, but they
# will not show up in IDEs unless they are listed in add_library.

# Add header files
file(GLOB HEADER_LIST CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/include/sdlxx/image/*.h")

# Add source files
set(SOURCE_LIST
    Image.cpp
    SDLXX_image.cpp)

# Make an automatic library - will be static or dynamic based on user setting
add_library(SDLXX_image ${HEADER_LIST} ${SOURCE_LIST})

# Set include directory and make it visible to users
target_include_directories(SDLXX_image PUBLIC "${PROJECT_SOURCE_DIR}/include")

# Add dependencies (TODO: Move to corresponding packages)
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(SDLXX_image PRIVATE SDL2::SDL2main SDL2::SDL2-static)
find_package(sdl2-image CONFIG REQUIRED)
target_link_libraries(SDLXX_image PRIVATE SDL2::SDL2_image)
find_package(sdl2-ttf CONFIG REQUIRED)
target_link_libraries(SDLXX_image PRIVATE SDL2::SDL2_ttf)
find_package(ZLIB REQUIRED)
target_link_libraries(SDLXX_image PRIVATE SDLXX_core
                      ZLIB::ZLIB)
# /Add dependencies (TODO: Move to corresponding packages)

# Set C++ standard to C++17
target_compile_features(SDLXX_image PRIVATE cxx_std_17)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include"
    PREFIX "Header Files"
    FILES ${HEADER_LIST})
