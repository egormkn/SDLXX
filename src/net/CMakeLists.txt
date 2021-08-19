# Note that headers are optional, and do not affect add_library,
# but they will not show up in IDEs unless they are listed in add_library.

# Add header files
file(GLOB HEADERS_LIST CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/include/sdlxx/net/**/*.h")

# Add source files
set(SOURCES_LIST
        net_api.cpp)

# Make an automatic library - will be static or dynamic based on user setting
add_library(sdlxx_net ${HEADERS_LIST} ${SOURCES_LIST})
add_library(sdlxx::net ALIAS sdlxx_net)
add_library(SDLXX::Net ALIAS sdlxx_net)

# Set include directory and make it visible to users
target_include_directories(sdlxx_net PUBLIC "${PROJECT_SOURCE_DIR}/include")

# Add dependencies
find_package(SDL2 CONFIG REQUIRED) # TODO: Remove
find_package(sdl2-net CONFIG REQUIRED)
target_link_libraries(sdlxx_net PUBLIC
                      sdlxx_core
                      SDL2::SDL2_net)

# Set C++ standard to C++17
target_compile_features(sdlxx_net PRIVATE cxx_std_17)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include"
             PREFIX "Header Files"
             FILES ${HEADERS_LIST})
