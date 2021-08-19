# Note that headers are optional, and do not affect add_library,
# but they will not show up in IDEs unless they are listed in add_library.

# Add header files
set(HEADERS_LIST
    Box2dDebugDraw.h
    game.h)

# Add source files
set(SOURCES_LIST
    Box2dDebugDraw.cpp
    main.cpp)

# Make an executable
add_executable(game ${HEADERS_LIST} ${SOURCES_LIST})

# Add dependencies
find_package(box2d CONFIG REQUIRED)
target_link_libraries(game PRIVATE
                      sdlxx::core
                      sdlxx::gui
                      sdlxx::image
                      sdlxx::ttf
                      box2d::box2d)

# Set C++ standard to C++17
target_compile_features(game PRIVATE cxx_std_17)

# Copy assets
file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# IDEs should put the headers in a nice place
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
             PREFIX "Header Files"
             FILES ${HEADERS_LIST})
