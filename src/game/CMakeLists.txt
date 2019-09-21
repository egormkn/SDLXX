# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/game/*.h")

# Add source files
set(SOURCE_LIST
    Box2DDrawer.cpp
    Game.cpp
    Menu.cpp
    main.cpp)

# Make an automatic library - will be static or dynamic based on user setting
add_executable(SDLXX_game ${HEADER_LIST} ${SOURCE_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(SDLXX_game PUBLIC "${PROJECT_SOURCE_DIR}/include/game")

# This depends on SDL2
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(SDLXX_game PRIVATE SDL2::SDL2main SDL2::SDL2-static)

# Temporary dependencies (TODO: Move to corresponding packages)
find_package(sdl2-image CONFIG REQUIRED)
target_link_libraries(SDLXX_game PRIVATE SDL2::SDL2_image)

find_package(sdl2-ttf CONFIG REQUIRED)
target_link_libraries(SDLXX_game PRIVATE SDL2::SDL2_ttf)

target_link_libraries(SDLXX_game PRIVATE SDLXX_core)

target_link_libraries(SDLXX_game PRIVATE SDLXX_gui)

target_link_libraries(SDLXX_game PRIVATE SDLXX_ttf)

target_link_libraries(SDLXX_game PRIVATE SDLXX_net)

target_link_libraries(SDLXX_game PRIVATE SDLXX_image)

target_link_libraries(SDLXX_game PRIVATE SDLXX_mixer)

target_link_libraries(SDLXX_game PRIVATE TMX)

find_package(unofficial-box2d CONFIG REQUIRED)
target_link_libraries(SDLXX_game PRIVATE unofficial::box2d::Box2D)

# All users of this library will need at least C++17
target_compile_features(SDLXX_game PUBLIC cxx_std_17)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include/game" PREFIX "Header Files" FILES ${HEADER_LIST})
