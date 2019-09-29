# Note that headers are optional, and do not affect add_library, but they
# will not show up in IDEs unless they are listed in add_library.

# Add header files
file(GLOB HEADER_LIST CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/include/sdlxx/gui/*.h")

# Add source files
set(SOURCE_LIST
    Button.cpp
    Scene.cpp
    SceneManager.cpp)

# Make an automatic library - will be static or dynamic based on user setting
add_library(SDLXX_gui ${HEADER_LIST} ${SOURCE_LIST})

# Set include directory and make it visible to users
target_include_directories(SDLXX_gui PUBLIC "${PROJECT_SOURCE_DIR}/include")

# Add dependencies (TODO: Move to corresponding packages)
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(SDLXX_gui PUBLIC SDL2::SDL2main SDL2::SDL2-static)
find_package(sdl2-image CONFIG REQUIRED)
target_link_libraries(SDLXX_gui PRIVATE SDL2::SDL2_image)
find_package(sdl2-ttf CONFIG REQUIRED)
target_link_libraries(SDLXX_gui PRIVATE SDL2::SDL2_ttf)
target_link_libraries(SDLXX_gui PRIVATE SDLXX_core)
# /Add dependencies (TODO: Move to corresponding packages)

# Set C++ standard to C++17
target_compile_features(SDLXX_gui PRIVATE cxx_std_17)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include"
    PREFIX "Header Files"
    FILES ${HEADER_LIST})
