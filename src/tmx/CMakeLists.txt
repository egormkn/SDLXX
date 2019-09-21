# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/tmx/*.h")

# Add source files
set(SOURCE_LIST
    TMX_Utils.cpp
    TMX_map.cpp
    TMX_tileset.cpp
    TMX_offset.cpp
    TMX_image.cpp
    TMX_layer.cpp
    TMX_data.cpp
    TMX_tile.cpp
    TMX_objectgroup.cpp
    TMX_object.cpp)

# Make an automatic library - will be static or dynamic based on user setting
add_library(TMX ${HEADER_LIST} ${SOURCE_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(TMX PUBLIC "${PROJECT_SOURCE_DIR}/include/tmx")

# This depends on TinyXML
find_package(tinyxml2 CONFIG REQUIRED)
target_link_libraries(TMX PRIVATE tinyxml2::tinyxml2)

target_link_libraries(TMX PRIVATE SDLXX_core)

# All users of this library will need at least C++17
target_compile_features(TMX PUBLIC cxx_std_17)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include/tmx" PREFIX "Header Files" FILES ${HEADER_LIST})



