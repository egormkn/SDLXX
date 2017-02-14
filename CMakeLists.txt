cmake_minimum_required(VERSION 3.7)

project(SDLXX CXX)
set(SRC_DIR "${PROJECT_SOURCE_DIR}/SDLXX")
set(CMAKE_DIR "${PROJECT_SOURCE_DIR}/cmake")
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_DIR}")
set(CMAKE_C_FLAGS_RELEASE "-DSDLXX_RELEASE")
set(CMAKE_CXX_FLAGS_RELEASE "-DSDLXX_RELEASE")

include(${CMAKE_DIR}/LibraryPaths.cmake OPTIONAL)

# You can set custom library paths in file /cmake/LibraryPaths.cmake
# For example:
# set(SDL2_DIR "C:\\Programs\\SDL2-2.0.5\\i686-w64-mingw32")
# set(SDL2_IMAGE_DIR "C:\\Programs\\SDL2_image-2.0.1\\i686-w64-mingw32")
# set(SDL2_MIXER_DIR "C:\\Programs\\SDL2_mixer-2.0.1\\i686-w64-mingw32")
# set(SDL2_NET_DIR "C:\\Programs\\SDL2_net-2.0.1\\i686-w64-mingw32")
# set(SDL2_TTF_DIR "C:\\Programs\\SDL2_ttf-2.0.14\\i686-w64-mingw32")
#
# See /cmake/README.md for library setup reference

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_net REQUIRED)
find_package(SDL2_mixer REQUIRED)

if (SDL2_FOUND)
    list(APPEND INCLUDE_DIRS ${SDL2_INCLUDE_DIR})
    list(APPEND DEFINES SDL2_FOUND)
endif ()
if (SDL2_IMAGE_FOUND)
    list(APPEND INCLUDE_DIRS ${SDL2_IMAGE_INCLUDE_DIR})
    list(APPEND DEFINES SDL2_IMAGE_FOUND)
endif ()
if (SDL2_TTF_FOUND)
    list(APPEND INCLUDE_DIRS ${SDL2_TTF_INCLUDE_DIR})
    list(APPEND DEFINES SDL2_TTF_FOUND)
endif ()
if (SDL2_NET_FOUND)
    list(APPEND INCLUDE_DIRS ${SDL2_NET_INCLUDE_DIR})
    list(APPEND DEFINES SDL2_NET_FOUND)
endif ()
if (SDL2_MIXER_FOUND)
    list(APPEND INCLUDE_DIRS ${SDL2_MIXER_INCLUDE_DIR})
    list(APPEND DEFINES SDL2_MIXER_FOUND)
endif ()

include_directories(${INCLUDE_DIRS})

set(SOURCE_FILES
    SDLXX/SDLXX.cpp
    SDLXX/SDLXX.h
    SDLXX/SDLXX_image.cpp
    SDLXX/SDLXX_image.h
    SDLXX/ttf/SDLXX_ttf.cpp
    SDLXX/ttf/SDLXX_ttf.h
    SDLXX/SDLXX_net.cpp
    SDLXX/SDLXX_net.h
    SDLXX/SDLXX_mixer.cpp
    SDLXX/SDLXX_mixer.h
    SDLXX/base/Window.cpp
    SDLXX/base/Window.h
    SDLXX/Exception.cpp
    SDLXX/Exception.h
    SDLXX/base/Renderer.cpp
    SDLXX/base/Renderer.h
    SDLXX/base/Texture.cpp
    SDLXX/base/Texture.h
    SDLXX/base/Animation.cpp
    SDLXX/base/Animation.h
    SDLXX/base/Color.cpp
    SDLXX/base/Color.h
    SDLXX/Utils.cpp
    SDLXX/Utils.h
    SDLXX/Log.cpp
    SDLXX/Log.h
    SDLXX/base/SceneManager.cpp
    SDLXX/base/SceneManager.h
    SDLXX/base/Scene.cpp
    SDLXX/base/Scene.h
    SDLXX/base/Event.cpp
    SDLXX/base/Event.h
    SDLXX/base/Rectangle.cpp
    SDLXX/base/Rectangle.h
    SDLXX/base/Point.cpp
    SDLXX/base/Point.h
    SDLXX/base/Surface.cpp 
    SDLXX/base/Surface.h
    SDLXX/base/Object.cpp
    SDLXX/base/Object.h
    SDLXX/ttf/Font.cpp
    SDLXX/ttf/Font.h
    SDLXX/gui/Button.cpp
    SDLXX/gui/Button.h
    SDLXX/network/tcp/TCPClient.cpp
    SDLXX/network/tcp/TCPClient.h
    SDLXX/network/tcp/TCPServer.cpp
    SDLXX/network/tcp/TCPServer.h)


add_library(TMX STATIC 
    SDLXX/tmx/TMX_Utils.cpp
    SDLXX/tmx/TMX_Utils.h
    SDLXX/tmx/TMX_map.cpp
    SDLXX/tmx/TMX_map.h
    SDLXX/tmx/TMX_tileset.cpp
    SDLXX/tmx/TMX_tileset.h
    SDLXX/tmx/TMX_offset.cpp
    SDLXX/tmx/TMX_offset.h
    SDLXX/tmx/TMX_image.cpp
    SDLXX/tmx/TMX_image.h
    SDLXX/tmx/TMX_layer.cpp
    SDLXX/tmx/TMX_layer.h
    SDLXX/tmx/TMX_data.cpp
    SDLXX/tmx/TMX_data.h
    tinyxml2/tinyxml2.cpp
    tinyxml2/tinyxml2.h)

add_library(SDLXX STATIC ${SOURCE_FILES})
target_compile_definitions(SDLXX PRIVATE ${DEFINES})
target_compile_features(SDLXX PRIVATE cxx_noexcept)

set(BOX2D_VERSION 2.3.2)
set(BOX2D_BUILD_STATIC TRUE)
add_subdirectory(Box2D/Box2D/Box2D)
include_directories(Box2D/Box2D)


# Game
add_executable(Game
    SDLXX/test/main.cpp
    SDLXX/test/Menu.h
    SDLXX/test/Menu.cpp
    SDLXX/test/Game.cpp
    SDLXX/test/Game.h SDLXX/test/Box2DDrawer.cpp SDLXX/test/Box2DDrawer.h)

target_link_libraries(Game
    Box2D
    SDLXX
    TMX
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${SDL2_TTF_LIBRARY}
    ${SDL2_NET_LIBRARY}
    ${SDL2_MIXER_LIBRARY})
