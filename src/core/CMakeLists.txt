# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# set(HEADER_LIST "${SDLXX_SOURCE_DIR}/include/core/Window.hpp")

# Optionally glob, but only for CMake 3.12 or later:
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/core/*.h")

# Add source files
set(SOURCE_LIST
    Animation.cpp
    Color.cpp
    Event.cpp 
    Exception.cpp
    Log.cpp
    Object.cpp 
    Point.cpp 
    Rectangle.cpp 
    Renderer.cpp 
    Scene.cpp 
    SceneManager.cpp 
    SDLXX.cpp
    Surface.cpp 
    Texture.cpp
    Utils.cpp
    Window.cpp)

# Make an automatic library - will be static or dynamic based on user setting
add_library(SDLXX_core ${HEADER_LIST} ${SOURCE_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(SDLXX_core PUBLIC "${PROJECT_SOURCE_DIR}/include/core")

# This depends on SDL2
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(SDLXX_core PRIVATE SDL2::SDL2main SDL2::SDL2-static)

# Temporary dependencies (TODO: Move to corresponding packages)
find_package(sdl2-image CONFIG REQUIRED)
target_link_libraries(SDLXX_core PRIVATE SDL2::SDL2_image)

find_package(sdl2-ttf CONFIG REQUIRED)
target_link_libraries(SDLXX_core PRIVATE SDL2::SDL2_ttf)

# All users of this library will need at least C++17
target_compile_features(SDLXX_core PUBLIC cxx_std_17)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include/core" PREFIX "Header Files" FILES ${HEADER_LIST})
