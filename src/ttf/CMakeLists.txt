# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/ttf/*.h")

# Add source files
set(SOURCE_LIST
    Font.cpp
    SDLXX_ttf.cpp)

# Make an automatic library - will be static or dynamic based on user setting
add_library(SDLXX_ttf ${HEADER_LIST} ${SOURCE_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(SDLXX_ttf PUBLIC "${PROJECT_SOURCE_DIR}/include/ttf")

# This depends on SDL2
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(SDLXX_ttf PRIVATE SDL2::SDL2main SDL2::SDL2-static)

# Temporary dependencies (TODO: Move to corresponding packages)
find_package(sdl2-image CONFIG REQUIRED)
target_link_libraries(SDLXX_ttf PRIVATE SDL2::SDL2_image)

find_package(sdl2-ttf CONFIG REQUIRED)
target_link_libraries(SDLXX_ttf PRIVATE SDL2::SDL2_ttf)

target_link_libraries(SDLXX_ttf PRIVATE SDLXX_core)

# All users of this library will need at least C++17
target_compile_features(SDLXX_ttf PUBLIC cxx_std_17)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include/ttf" PREFIX "Header Files" FILES ${HEADER_LIST})
