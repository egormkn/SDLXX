cmake_minimum_required(VERSION 3.7)

project(SDL2XX CXX)
set(SRC_DIR "${PROJECT_SOURCE_DIR}/SDL2XX")
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
    SDL2XX/SDL2XX.cpp
    SDL2XX/SDL2XX.h
    SDL2XX/Window.cpp
    SDL2XX/Window.h
    SDL2XX/Exception.cpp
    SDL2XX/Exception.h
    SDL2XX/Renderer.cpp
    SDL2XX/Renderer.h
    SDL2XX/Texture.cpp
    SDL2XX/Texture.h
    SDL2XX/Animation.cpp
    SDL2XX/Animation.h
    SDL2XX/Color.cpp
    SDL2XX/Color.h
    SDL2XX/Utils.cpp
    SDL2XX/Utils.h)

add_library(SDL2XX ${SOURCE_FILES})
target_compile_definitions(SDL2XX PUBLIC ${DEFINES})
target_compile_features(SDL2XX PRIVATE cxx_noexcept)

# Test program
add_executable(SDL2XXtest SDL2XX/Test.cpp)
target_link_libraries(SDL2XXtest SDL2XX
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${SDL2_TTF_LIBRARY}
    ${SDL2_NET_LIBRARY}
    ${SDL2_MIXER_LIBRARY})