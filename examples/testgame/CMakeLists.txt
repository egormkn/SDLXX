# Note that headers are optional, and do not affect add_library, but they
# will not show up in IDEs unless they are listed in add_library.

# Add header files
set(HEADER_LIST
    Box2DDrawer.h
    Game.h
    Menu.h)

# Add source files
set(SOURCE_LIST
    Box2DDrawer.cpp
    Game.cpp
    Menu.cpp
    main.cpp)

# Make an executable
add_executable(SDLXX_game ${HEADER_LIST} ${SOURCE_LIST})

# Add dependencies
find_package(box2d CONFIG REQUIRED)
target_link_libraries(SDLXX_game PRIVATE
    SDLXX_core
    SDLXX_gui
    SDLXX_ttf
    SDLXX_net
    SDLXX_image
    SDLXX_mixer
    TMX
    box2d::box2d)

# Set C++ standard to C++17
target_compile_features(SDLXX_game PRIVATE cxx_std_17)

# IDEs should put the headers in a nice place
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
    PREFIX "Header Files"
    FILES ${HEADER_LIST})

# Copy assets to the build directory
add_custom_command(TARGET SDLXX_game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:SDLXX_game>/resources)
