# Note that headers are optional, and do not affect add_library, but they
# will not show up in IDEs unless they are listed in add_library.

# Add header files
file(GLOB HEADER_LIST CONFIGURE_DEPENDS
    "../../examples/game/tmx/*.h")

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

# Set include directory and make it visible to users
target_include_directories(TMX PUBLIC "../../../include")

# Add dependencies
find_package(tinyxml2 CONFIG REQUIRED)
target_link_libraries(TMX PRIVATE tinyxml2::tinyxml2)

# Set C++ standard to C++17
target_compile_features(TMX PRIVATE cxx_std_17)

# IDEs should put the headers in a nice place
source_group(TREE "../../../include"
    PREFIX "Header Files"
    FILES ${HEADER_LIST})
