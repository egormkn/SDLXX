# Note that headers are optional, and do not affect add_library, but they
# will not show up in IDEs unless they are listed in add_library.

# Add header files
file(GLOB HEADER_LIST CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/include/sdlxx/mixer/*.h")

# Add source files
set(SOURCE_LIST
    SDLXX_mixer.cpp)

# Make an automatic library - will be static or dynamic based on user setting
add_library(SDLXX_mixer ${HEADER_LIST} ${SOURCE_LIST})

# Set include directory and make it visible to users
target_include_directories(SDLXX_mixer PUBLIC "${PROJECT_SOURCE_DIR}/include")

# Add dependencies (TODO: Move to corresponding packages)
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(SDLXX_mixer PRIVATE SDL2::SDL2main SDL2::SDL2-static)
find_package(sdl2-mixer CONFIG REQUIRED)
target_link_libraries(SDLXX_mixer PRIVATE SDL2::SDL2_mixer)

target_link_libraries(SDLXX_mixer PRIVATE SDLXX_core)
# /Add dependencies (TODO: Move to corresponding packages)

# Set C++ standard to C++17
target_compile_features(SDLXX_mixer PRIVATE cxx_std_17)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include"
    PREFIX "Header Files"
    FILES ${HEADER_LIST})
