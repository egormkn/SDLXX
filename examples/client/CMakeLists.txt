cmake_minimum_required(VERSION 3.6)

project(SDLgame)

message("Game Client")

add_executable(SDLgame src/main.cpp)
set_property(TARGET SDLgame PROPERTY CXX_STANDARD 11)

target_link_libraries(SDLgame
    TinyXML
    Logger
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${SDL2_TTF_LIBRARY}
    ${SDL2_NET_LIBRARY}
    ${SDL2_MIXER_LIBRARY})