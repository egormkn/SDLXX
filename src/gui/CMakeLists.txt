# Note that headers are optional, and do not affect add_library,
# but they will not show up in IDEs unless they are listed in add_library.

# Add header files
file(GLOB HEADERS_LIST CONFIGURE_DEPENDS
     "${PROJECT_SOURCE_DIR}/include/sdlxx/gui/**/*.h")

# Add source files
set(SOURCES_LIST
    button.cpp
    layout.cpp
    node.cpp
    parent_node.cpp
    scene.cpp
    scene_manager.cpp
    style.cpp)

# Make an automatic library - will be static or dynamic based on user setting
add_library(sdlxx_gui ${HEADERS_LIST} ${SOURCES_LIST})
add_library(sdlxx::gui ALIAS sdlxx_gui)
add_library(SDLXX::GUI ALIAS sdlxx_gui)

# Set include directory and make it visible to users
target_include_directories(sdlxx_gui PUBLIC "${PROJECT_SOURCE_DIR}/include")

# Add dependencies
target_link_libraries(sdlxx_gui PUBLIC
                      sdlxx_core
                      sdlxx_image
                      sdlxx_ttf)

# Set C++ standard to C++17
target_compile_features(sdlxx_gui PRIVATE cxx_std_17)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include"
             PREFIX "Header Files"
             FILES ${HEADERS_LIST})
