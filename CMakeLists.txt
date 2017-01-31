cmake_minimum_required(VERSION 3.7)

project(SDLXX CXX)
set(SRC_DIR "${PROJECT_SOURCE_DIR}/SDLXX")
set(CMAKE_DIR "${PROJECT_SOURCE_DIR}/cmake")
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_DIR}")

include(${CMAKE_DIR}/LibraryPaths.cmake OPTIONAL)

# You can set custom library paths in file /cmake/LibraryPaths.cmake
# For example:
# set(SDL2_DIR "C:\\Programs\\SDL2-2.0.4\\i686-w64-mingw32")
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
    SDLXX/SDLXX_image.cpp
    SDLXX/SDLXX_image.h
    SDLXX/SDLXX_ttf.cpp
    SDLXX/SDLXX_ttf.h
    SDLXX/SDLXX_net.cpp
    SDLXX/SDLXX_net.h
    SDLXX/SDLXX_mixer.cpp
    SDLXX/SDLXX_mixer.h
    SDLXX/Log.cpp
    SDLXX/Log.h
    SDLXX/base/SceneManager.cpp
    SDLXX/base/SceneManager.h
    SDLXX/base/Scene.cpp
    SDLXX/base/Scene.h
    SDLXX/base/Event.cpp
    SDLXX/base/Event.h)

add_library(SDLXX ${SOURCE_FILES})
target_compile_definitions(SDLXX PUBLIC ${DEFINES})
target_compile_features(SDLXX PRIVATE cxx_noexcept)

# Test program
add_executable(SDLXXtest SDLXX/Test.cpp SDLXX/base/SceneTest.h SDLXX/base/SceneTest.cpp )
# SDLXX/base/Dot.cpp SDLXX/base/Dot.h SDLXX/base/Tile.cpp SDLXX/base/Tile.h
target_link_libraries(SDLXXtest SDLXX
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${SDL2_TTF_LIBRARY}
    ${SDL2_NET_LIBRARY}
    ${SDL2_MIXER_LIBRARY})