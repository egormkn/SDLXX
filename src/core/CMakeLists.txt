# Note that headers are optional, and do not affect add_library,
# but they will not show up in IDEs unless they are listed in add_library.

# Add header files
file(GLOB HEADERS_LIST CONFIGURE_DEPENDS
     "${PROJECT_SOURCE_DIR}/include/sdlxx/core/**/*.h")

# Add source files
set(SOURCES_LIST
    blendmode.cpp
    color.cpp
    core_api.cpp
    dimensions.cpp
    display.cpp
    events.cpp
    exception.cpp
    gl.cpp
    log.cpp
    point.cpp
    rectangle.cpp
    renderer.cpp
    surface.cpp
    texture.cpp
    time.cpp
    timer.cpp
    version.cpp
    window.cpp)

# Make an automatic library - will be static or dynamic based on user setting
add_library(sdlxx_core ${HEADERS_LIST} ${SOURCES_LIST})
add_library(sdlxx::core ALIAS sdlxx_core)
add_library(SDLXX::Core ALIAS sdlxx_core)

# Set include directory and make it visible to users
target_include_directories(sdlxx_core PUBLIC "${PROJECT_SOURCE_DIR}/include")

# Add dependencies
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(sdlxx_core PUBLIC
                      SDL2::SDL2
                      SDL2::SDL2main)

# Set C++ standard to C++17
target_compile_features(sdlxx_core PRIVATE cxx_std_17)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include"
             PREFIX "Header Files"
             FILES ${HEADERS_LIST})
